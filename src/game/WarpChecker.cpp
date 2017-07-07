#include "WarpChecker.h"
#include <Box2D/Dynamics/b2Fixture.h>

WarpChecker::WarpChecker(b2Vec2 worldSize)
{
    _worldSize = worldSize;
}

bool WarpChecker::ReportFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();
    b2Vec2 pos = body->GetPosition();

    if(pos.x < -1.f) pos.x += 1.f+_worldSize.x;
    else if(pos.x > _worldSize.x) pos.x -= 1.f+_worldSize.x;

    if(pos.y < -1.f) pos.y += 1.f+_worldSize.y;
    else if(pos.y > _worldSize.y) pos.y -= 1.f+_worldSize.y;

    body->SetTransform(pos, body->GetAngle());

    return true;
}
