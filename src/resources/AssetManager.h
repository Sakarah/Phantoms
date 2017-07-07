#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>

class AssetManager
{
public:
    enum Tileset
    {
        Sprite,
        Background,
        Border,
        HelpSettings,
        NbTilesets // Keep at end !
    };

    enum Font
    {
        Gui,
        GameOver,
        Victory,
        Keyboard,
        NbFonts // Keep at end !
    };

    enum Shader
    {
        LightAttenuation,
        Blur,
        NbShaders // Keep at end !
    };

    static void loadAssets();
    static sf::Texture* getTileset(Tileset);
    static sf::Font& getFont(Font);
    static sf::Shader* getShader(Shader);

private:
    static sf::Texture _tilesets[NbTilesets];
    static sf::Font _fonts[NbFonts];
    static sf::Shader _shaders[NbShaders];
};

#endif // ASSETMANAGER_H
