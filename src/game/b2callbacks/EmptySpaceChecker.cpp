#include "EmptySpaceChecker.h"
#include <Box2D/Dynamics/b2Fixture.h>

EmptySpaceChecker::EmptySpaceChecker(uint16 categoryMask)
{
    _categoryMask = categoryMask;
    _result = true;
}

bool EmptySpaceChecker::ReportFixture(b2Fixture* fixture)
{
    if(fixture->GetFilterData().categoryBits & _categoryMask) _result = false;
    return _result;
}

bool EmptySpaceChecker::isEmpty() { return _result; }
