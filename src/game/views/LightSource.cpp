#include "LightSource.h"
#include "../VerticesLister.h"
#include "../NearestObjectRaycaster.h"
#include "../World.h"
#include <Box2D/Dynamics/b2World.h>

const float LIGHT_ANGLE_OFFSET = 0.00001;
const float PI = std::acos(-1);

LightSource::LightSource(b2Vec2 pos, float radius, sf::Color color)
{
    _pos = pos;
    _radius = radius;
    _color = color;
}

void LightSource::computeLight(const b2World* world)
{
    b2Vec2 centerPoint = center();

    b2AABB lightAABB;
    lightAABB.lowerBound = centerPoint - _radius*b2Vec2(1,1);
    lightAABB.upperBound = centerPoint + _radius*b2Vec2(1,1);

    VerticesLister verticesLister(LightOccluderFlag);
    world->QueryAABB(&verticesLister, lightAABB);
    std::vector<b2Vec2>& occluderVertices = verticesLister.getVertices();

    std::vector<float> rayAngles;
    rayAngles.reserve(3*occluderVertices.size());
    for(b2Vec2 occluderVertex : occluderVertices)
    {
        b2Vec2 occluderDir = occluderVertex - centerPoint;
        float angle = std::atan2(occluderDir.y, occluderDir.x);
        rayAngles.push_back(angle+LIGHT_ANGLE_OFFSET);
        rayAngles.push_back(angle-LIGHT_ANGLE_OFFSET);
    }

    rayAngles.push_back(-3*PI/4);
    rayAngles.push_back(-PI/4);
    rayAngles.push_back(PI/4);
    rayAngles.push_back(3*PI/4);

    std::sort(rayAngles.begin(), rayAngles.end());

    _lightVertices.setPrimitiveType(sf::TrianglesFan);
    _lightVertices.append(sf::Vertex(toScreenPos(centerPoint)));

    for(uint i = 0 ; i <= rayAngles.size() ; i++)
    {
        float rayAngle = rayAngles[i%rayAngles.size()];
        b2Vec2 rayDir = b2Vec2(std::cos(rayAngle), std::sin(rayAngle));
        b2Vec2 rayEnd = centerPoint + std::sqrt(2)*_radius*rayDir;

        NearestObjectRaycaster raycaster = NearestObjectRaycaster(LightOccluderFlag);
        world->RayCast(&raycaster, centerPoint, rayEnd);

        if(raycaster.objectTouched()) rayEnd = raycaster.contactPoint();
        _lightVertices.append(sf::Vertex(toScreenPos(rayEnd)));
    }
}

b2Vec2 LightSource::pos() { return _pos; }
b2Vec2 LightSource::center() { return _pos + b2Vec2(0.5,0.5); }
float LightSource::radius() { return _radius; }
sf::Color LightSource::color() { return _color; }
const sf::VertexArray& LightSource::lightVertices() { return _lightVertices; }

sf::VertexArray LightSource::passingWallsVertices()
{
    b2Vec2 centerPoint = center();
    sf::VertexArray passingWallsVertices(sf::Quads, 4);
    passingWallsVertices[0].position = toScreenPos(centerPoint + _radius*b2Vec2(-1,-1));
    passingWallsVertices[1].position = toScreenPos(centerPoint + _radius*b2Vec2(+1,-1));
    passingWallsVertices[2].position = toScreenPos(centerPoint + _radius*b2Vec2(+1,+1));
    passingWallsVertices[3].position = toScreenPos(centerPoint + _radius*b2Vec2(-1,+1));
    return passingWallsVertices;
}
