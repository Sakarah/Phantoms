#ifndef VERTICESLISTER_H
#define VERTICESLISTER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <vector>

class VerticesLister : public b2QueryCallback
{
public:
    VerticesLister(uint16 categoryMask);
    ~VerticesLister() = default;
    bool ReportFixture(b2Fixture* fixture) override;
    std::vector<b2Vec2>& getVertices();
private:
    uint16 _categoryMask;
    std::vector<b2Vec2> _vertices;
};

#endif // VERTICESLISTER_H
