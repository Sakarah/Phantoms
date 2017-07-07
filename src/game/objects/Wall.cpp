#include "Wall.h"
#include "../World.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

Wall::Wall(ObjectSprite type, b2Vec2 pos) : Object(type, pos)
{
    _flags = WallFlag | LightOccluderFlag;
}

void Wall::addToWorld(World* world)
{
    _world = world;
    b2World* physicWorld = world->physicWorld();

    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    bodyDef.position = _startPos;
    bodyDef.type = b2_staticBody;
    _physicBody = physicWorld->CreateBody(&bodyDef);

    b2Fixture* fix = createSquareFixture(b2Vec2(0.5,0.5), _sprite == ObjectSprite::Door ? b2Vec2(0.5,0.3) : b2Vec2(0.5,0.5));

    b2Fixture* extendedFix = nullptr;
    if(_startPos.x == 0) extendedFix = createSquareFixture(b2Vec2(-0.5,0.5));
    if(_startPos.y == 0) extendedFix = createSquareFixture(b2Vec2(0.5,-0.5));
    if(_startPos.x == _world->size().x-1.f) extendedFix = createSquareFixture(b2Vec2(1.5,0.5));
    if(_startPos.y == _world->size().y-1.f) extendedFix = createSquareFixture(b2Vec2(0.5,1.5));

    b2Filter filter;
    filter.categoryBits = WallFlag | LightOccluderFlag;
    filter.maskBits = CharacterFlag | PhantomFlag;
    fix->SetFilterData(filter);
    if(extendedFix) extendedFix->SetFilterData(filter);
}

b2Fixture* Wall::createSquareFixture(b2Vec2 center, b2Vec2 halfSize)
{
    b2FixtureDef fixDef;
    b2PolygonShape squareShape;
    squareShape.SetAsBox(halfSize.x, halfSize.y, center, 0);
    fixDef.shape = &squareShape;
    fixDef.friction = 0.f;
    return _physicBody->CreateFixture(&fixDef);
}

void Wall::linkedSwitchActivated(bool active)
{
    _physicBody->SetActive(!active);
}
