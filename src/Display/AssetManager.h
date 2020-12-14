#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <map>

namespace turbohikerSFML {
    class AssetManager {
    public:
        AssetManager() = default;
        ~AssetManager() = default;

        void loadTexture(const std::string &name, const std::string &texturePath);
        sf::Texture &getTexture(std::string name);
        void loadFont(const std::string &name, const std::string &fontPath);
        sf::Font &getFont(std::string name);

//        void loadAudio(const std::string &name, const std::string &audioPath);
//        sf::Music &getAudio(std::string name);
    private:
        std::map<std::string, sf::Texture> texMap;
        std::map<std::string, sf::Font> fontMap;
//        std::map<std::string, sf::Music> audioMap;
    };
}