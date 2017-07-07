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
using std::unique_ptr;

template<typename ... Args>
std::string formatString(const std::string& format, Args... args)
{
    size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

#include <locale>
#include <codecvt>
// We need wide strings for SFML but gettext provides utf8 strings
inline std::wstring toWideStr(const std::string& str)
{   
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes(str);
}

#include <libintl.h>
#define tr(str) gettext(str) // Translation
#define _tr_(str) str // Noop translation
#define wtr(str) toWideStr(tr(str)) // Translation and wstring conversion
#define ntr(str1, str2, n) ngettext(str1, str2, n) // Translation with plural form
#define nftr(str1, str2, n) formatString(ntr(str1,str2,n),n) // Translation and formatting (plural form)
#define wnftr(str1, str2, n) toWideStr(nftr(str1,str2,n)) // Same as nftr but returns a wstring
#define wfmt(format, ...)  toWideStr(formatString(format, __VA_ARGS__)) // Format and convert to wide string

// Note : Indexes are linked to the sprite position in tileset
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

