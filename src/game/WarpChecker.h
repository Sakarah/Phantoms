#ifndef WARPCHECKER_H
#define WARPCHECKER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "../common.h"

class WarpChecker : public b2QueryCallback
{
public:
    WarpChecker(b2Vec2 worldSize);
    ~WarpChecker() = default;
    bool ReportFixture(b2Fixture* fixture) override;
private:
    b2Vec2 _worldSize;
};

#endif // WARPCHECKER_H
