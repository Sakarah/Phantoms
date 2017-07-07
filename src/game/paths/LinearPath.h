#ifndef LINEARPATH_H
#define LINEARPATH_H

#include "Path.h"

class LinearPath : public Path
{
public:
    LinearPath();
    ~LinearPath() = default;
    void reset() override;
protected:
    float travelToNextPoint(float distToTravelSqr) override;
private:
    int _nextPointId;
};

#endif // LINEARPATH_H
