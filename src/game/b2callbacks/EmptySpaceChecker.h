#ifndef EMPTYSPACECHECKER_H
#define EMPTYSPACECHECKER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "common.h"

class EmptySpaceChecker : public b2QueryCallback
{
public:
    EmptySpaceChecker(uint16 categoryMask);
    ~EmptySpaceChecker() = default;
    bool ReportFixture(b2Fixture* fixture) override;
    bool isEmpty();
private:
    uint16 _categoryMask;
    bool _result;
};

#endif // EMPTYSPACECHECKER_H
