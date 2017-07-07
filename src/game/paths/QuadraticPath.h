#ifndef QUADRATICPATH_H
#define QUADRATICPATH_H

#include "Path.h"

class QuadraticPath : public Path
{
public:
    QuadraticPath();
    ~QuadraticPath() = default;
    void reset() override;
protected:
    float travelToNextPoint(float distToTravelSqr) override;
private:
    b2Vec2 getQuadPoint(float progress, b2Vec2 start, b2Vec2 inflex, b2Vec2 end);
    b2Vec2 getQuadPoint(float progress);
    int _lastPointId;
    double _currentProgress;
};

#endif // QUADRATICPATH_H
