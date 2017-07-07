#include "LinearPath.h"

LinearPath::LinearPath()
{
    _nextPointId = 0;
}

void LinearPath::reset() { _nextPointId = 0; }

float LinearPath::travelToNextPoint(float distToTravelSqr)
{
    b2Vec2 currentPos = _object->currentPos();
    b2Vec2 destination = _points[_nextPointId];
    b2Vec2 lineVect = destination-currentPos;

    float distToNextPointSqr = lineVect.LengthSquared();
    if(distToTravelSqr >= distToNextPointSqr)
    {
        _object->jumpToPos(destination);
        _nextPointId++;
        _nextPointId %= _points.size();

        return distToTravelSqr - distToNextPointSqr;
    }
    else
    {
        float ratioSqr = distToTravelSqr/distToNextPointSqr;
        float ratio = std::sqrt(ratioSqr);
        lineVect *= ratio;
        _object->jumpToPos(currentPos + lineVect);

        return 0;
    }
}
