#include "Path.h"
#include "../gameplay.h"

Path::Path()
{
    _object = nullptr;
}

void Path::addPoint(b2Vec2 point)
{
    _points.push_back(point);
}

void Path::setObject(Object* obj)
{
    _object = obj;
}

void Path::step(float time)
{
    if(!_object) return;

    float distToTravelSqr = time*_object->velocity();
    distToTravelSqr *= distToTravelSqr;

    while(distToTravelSqr > PATH_PRECISION) distToTravelSqr = travelToNextPoint(distToTravelSqr);
}
