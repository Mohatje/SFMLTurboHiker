#pragma once
#include <iostream>
#include <map>
#include <SFML/Window/Keyboard.hpp>



namespace turbohikerSFML {
    class KeyConfigHelper {
    public:

        /**
         * Static method to convert characters to sf::Keyboard::Keys
         * @param keyIndentifier the to be converted character
         * @return sf::Keyboard::Key which corresponds with the given input
         */
        static sf::Keyboard::Key keyboardFromString(const std::string &keyIndentifier);

        /**
         * Getter to get the singleton instance of the KeyConfigHelper
         * @return KeyConfigHelper singleton
         */
        static KeyConfigHelper &getInstance();

    private:
        KeyConfigHelper();
        KeyConfigHelper(const KeyConfigHelper& cpy);
        KeyConfigHelper& operator=(const KeyConfigHelper& rhs);
        ~KeyConfigHelper() = default;

        std::map<std::string, sf::Keyboard::Key> keyMap;
    };

}
