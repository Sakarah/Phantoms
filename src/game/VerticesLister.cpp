#include "VerticesLister.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

VerticesLister::VerticesLister(uint16 categoryMask)
{
    _categoryMask = categoryMask;
}

bool VerticesLister::ReportFixture(b2Fixture *fixture)
{
    if(fixture->GetFilterData().categoryBits & _categoryMask)
    {
        if(fixture->GetType() == b2Shape::e_polygon)
        {
            b2PolygonShape* shape = static_cast<b2PolygonShape*>(fixture->GetShape());
            for(int i = 0 ; i < shape->GetVertexCount() ; i++)
            {
                _vertices.push_back(fixture->GetBody()->GetPosition() + shape->GetVertex(i));
            }
        }
    }

    return true;
}

std::vector<b2Vec2>& VerticesLister::getVertices()
{
    return _vertices;
}
