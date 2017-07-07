#include "QuadraticPath.h"

QuadraticPath::QuadraticPath()
{
    _currentProgress = 0.;
    _lastPointId = 0;
}

void QuadraticPath::reset()
{
    _currentProgress = 0.;
    _lastPointId = 0;
}

float QuadraticPath::travelToNextPoint(float distToTravelSqr)
{
    b2Vec2 currentPos = _object->currentPos();
    b2Vec2 endPos = _points[(_lastPointId+2)%_points.size()];
    float distToNextPointSqr = (endPos-currentPos).LengthSquared();
    if(distToTravelSqr > distToNextPointSqr)
    {
        _object->jumpToPos(endPos);
        _currentProgress = 0.;
        _lastPointId += 2;
        _lastPointId %= _points.size();

        return distToTravelSqr - distToNextPointSqr;
    }
    else
    {
        double endProgress = 1.;
        while(distToTravelSqr < distToNextPointSqr)
        {
            endProgress = (_currentProgress+endProgress)/2;
            endPos = getQuadPoint(endProgress);
            distToNextPointSqr = (endPos-currentPos).LengthSquared();
        }
        _currentProgress = endProgress;
        _object->jumpToPos(endPos);

        return distToTravelSqr - distToNextPointSqr;
    }
}

b2Vec2 QuadraticPath::getQuadPoint(float progress, b2Vec2 start, b2Vec2 inflex, b2Vec2 end)
{
    b2Vec2 result(0,0);
    result += (1-progress)*(1-progress)*start;
    result += 2*(1-progress)*progress*inflex;
    result += progress*progress*end;
    return result;
}

b2Vec2 QuadraticPath::getQuadPoint(float progress)
{
    b2Vec2 start = _points[_lastPointId];
    b2Vec2 inflex = _points[_lastPointId+1];
    b2Vec2 end = _points[(_lastPointId+2)%_points.size()];
    return getQuadPoint(progress, start, inflex, end);
}
