#pragma once
#include <iostream>
#include <map>
#include <SFML/Window/Keyboard.hpp>



namespace turbohikerSFML {
    class KeyConfigHelper {
    public:
        static sf::Keyboard::Key keyboardFromString(const std::string &keyIndentifier);

        static KeyConfigHelper &getInstance();

    private:
        KeyConfigHelper();
        KeyConfigHelper(const KeyConfigHelper& cpy);
        KeyConfigHelper& operator=(const KeyConfigHelper& rhs);
        ~KeyConfigHelper() = default;

        std::map<std::string, sf::Keyboard::Key> keyMap;
    };

}
