#ifndef PATH_H
#define PATH_H

#include "../objects/Object.h"

class Path
{
public:
    Path();
    virtual ~Path() = default;
    void addPoint(b2Vec2 point);
    void setObject(Object*);
    virtual void reset() = 0;
    void step(float time);
protected:
    virtual float travelToNextPoint(float distToTravelSqr) = 0;

    Object* _object;
    std::vector<b2Vec2> _points;
};

#endif // PATH_H
