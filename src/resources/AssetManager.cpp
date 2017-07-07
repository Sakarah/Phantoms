#include "AssetManager.h"

sf::Texture AssetManager::_tilesets[AssetManager::NbTilesets];
const std::string TILESET_FILE[AssetManager::NbTilesets] = { "sprite.png", "background.png", "border.png", "helpSettings.png" };

sf::Font AssetManager::_fonts[AssetManager::NbFonts];
const std::string FONT_FILE[AssetManager::NbFonts] = { "gui.ttf", "gameOver.ttf", "victory.ttf", "keyboard.ttf" };

sf::Shader AssetManager::_shaders[AssetManager::NbShaders];
const std::pair<std::string,std::string> SHADER_FILES[AssetManager::NbShaders] = { {"", "lightAttenuation.frag"}, {"", "blur.frag"} };

void AssetManager::loadAssets()
{
    for(int i = 0 ; i < NbTilesets ; i++) _tilesets[i].loadFromFile("assets/tileset/"+TILESET_FILE[i]);
    for(int i = 0 ; i < NbFonts ; i++) _fonts[i].loadFromFile("assets/font/"+FONT_FILE[i]);
    for(int i = 0 ; i < NbShaders ; i++)
    {
        if(SHADER_FILES[i].second.empty()) _shaders[i].loadFromFile("assets/shader/"+SHADER_FILES[i].first, sf::Shader::Vertex);
        else if(SHADER_FILES[i].first.empty()) _shaders[i].loadFromFile("assets/shader/"+SHADER_FILES[i].second, sf::Shader::Fragment);
        else _shaders[i].loadFromFile("assets/shader/"+SHADER_FILES[i].first, "assets/shader/"+SHADER_FILES[i].second);
    }
}

sf::Texture* AssetManager::getTileset(Tileset texture) { return &_tilesets[texture]; }
sf::Font& AssetManager::getFont(Font font) { return _fonts[font]; }
sf::Shader* AssetManager::getShader(Shader shader) { return &_shaders[shader]; }
