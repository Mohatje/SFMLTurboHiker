#include "AssetManager.h"


namespace turbohikerSFML {
    void AssetManager::loadTexture(const std::string &name, const std::string &texturePath) {
        sf::Texture texture;
        if (texture.loadFromFile(texturePath)) {
            texMap[name] = texture;
        }
    }

    sf::Texture &AssetManager::getTexture(std::string name) {
        return texMap.at(name);
    }

    void AssetManager::loadFont(const std::string &name, const std::string &texturePath) {
        sf::Font font;
        if (font.loadFromFile(texturePath)) {
            fontMap[name] = font;
        }
    }

    sf::Font &AssetManager::getFont(std::string name) {
        return fontMap.at(name);
    }
}
