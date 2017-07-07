#include "NearestObjectRaycaster.h"
#include <Box2D/Dynamics/b2Fixture.h>

NearestObjectRaycaster::NearestObjectRaycaster(uint16 categoryMask)
{
    _categoryMask = categoryMask;
    _fraction = 1;
}

float32 NearestObjectRaycaster::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& /*normal*/, float32 fraction)
{
    if(!(fixture->GetFilterData().categoryBits & _categoryMask)) return -1;

    _contactPoint = point;
    _fraction = fraction;
    return fraction;
}

bool NearestObjectRaycaster::objectTouched() { return _fraction != 1; }
b2Vec2 NearestObjectRaycaster::contactPoint() { return _contactPoint; }
float32 NearestObjectRaycaster::getFraction() { return _fraction; }
