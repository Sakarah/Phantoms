#ifndef NEARESTOBJECTRAYCASTER_H
#define NEARESTOBJECTRAYCASTER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Common/b2Math.h>

class NearestObjectRaycaster : public b2RayCastCallback
{
public:
    NearestObjectRaycaster(uint16 categoryMask);
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
    bool objectTouched();
    b2Vec2 contactPoint();
    float32 getFraction();
private:
    uint16 _categoryMask;
    b2Vec2 _contactPoint;
    float32 _fraction;
};

#endif // NEARESTOBJECTRAYCASTER_H
