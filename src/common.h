#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Common/b2Settings.h>

using std::shared_ptr;
using std::weak_ptr;

// Note : Les indexs correspondent à la position des sprites dans le tileset
enum class ObjectSprite
{
    Empty = -1,
    Character1 = 0,
    Character2 = 8,
    Character3 = 16,
    Character4 = 24,
    Phantom = 1,
    PhantomExplosive = 9,
    PhantomPatroller = 17,
    PhantomFast = 25,
    PhantomKiller = 33,
    PhantomPlayer = 32,
    Wall = 2,
    WallAlt = 3,
    Life = 4,
    Power = 5,
    Lock = 6,
    Key = 7,
    Coin = 10,
    Coin2 = 11,
    Crystal = 12,
    BlackCoin = 23,
    BlackCrystal = 13,
    SwitchOn = 14,
    SwitchOff = 15,
    Door = 18,
    Chest = 19,
    Bomb = 20,
    Teleporter = 21,
    Sword = 22,
    Boss = 26,
    VulnerableBoss = 28,
};

enum ObjectFlag : uint16
{
    NoFlag = 0x0,
    WallFlag = 0x1,
    CharacterFlag = 0x2,
    PhantomFlag = 0x4,
    ItemFlag = 0x8,
    CoinFlag = 0x10,
    BigSpriteFlag = 0x20,
    SemiTransparentFlag = 0x40,
    LightOccluderFlag = 0x80,
    DisabledFlag = 0x100,
    NeverDisabledFlag = 0x200,
    AllFlags = 0xffff
};

enum class LevelType
{
    Classic,
    Bonus,
    Boss,
    Duel,
    End
};

enum class GameEnd
{
    NotEnded,
    GameOver,
    Victory,
    DuelVictoryPlayer,
    DuelVictoryPhantom
};

const int TILE_SIZE = 32;
inline sf::Vector2i toPixelPos(b2Vec2 vec)
{
    return sf::Vector2i(TILE_SIZE * vec.x, TILE_SIZE * vec.y);
}
inline sf::Vector2u toPixelSize(b2Vec2 vec)
{
    return sf::Vector2u(TILE_SIZE * vec.x, TILE_SIZE * vec.y);
}
inline sf::Vector2f toScreenPos(b2Vec2 vec)
{
    return sf::Vector2f(TILE_SIZE * vec.x, TILE_SIZE * vec.y);
}
inline sf::Vector2f toGLCoords(sf::Vector2f vec, sf::Vector2u viewportSize)
{
    return sf::Vector2f(vec.x + 0.5, viewportSize.y - vec.y + 0.5);
}

#endif // COMMON_H

