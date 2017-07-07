#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <SFML/Graphics/Drawable.hpp>
#include <Box2D/Common/b2Draw.h>
#include "../World.h"

class PhysicsDebugDraw : public b2Draw, public sf::Drawable
{
public:
    PhysicsDebugDraw();
    ~PhysicsDebugDraw() = default;
    void setupDebugDraw(World*);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    void DrawTransform(const b2Transform& xf) override;

private:
    World* _world;
    mutable sf::RenderTarget* _renderTarget;
    mutable sf::RenderStates _renderStates;
};

#endif // DEBUGDRAW_H
