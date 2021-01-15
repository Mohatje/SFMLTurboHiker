#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <map>

namespace turbohikerSFML {
class KeyConfigHelper
{
public:
        /**
         * Static method to convert characters to sf::Keyboard::Keys
         * @param keyIdentifier the to be converted character
         * @return sf::Keyboard::Key which corresponds with the given input
         */
        static sf::Keyboard::Key keyboardFromString(const std::string& keyIdentifier);

        /**
         * Getter to get the singleton instance of the KeyConfigHelper
         * @return KeyConfigHelper singleton
         */
        static KeyConfigHelper& getInstance();

private:
        KeyConfigHelper();
        KeyConfigHelper(const KeyConfigHelper& cpy);
        KeyConfigHelper& operator=(const KeyConfigHelper& rhs);
        ~KeyConfigHelper() = default;

        std::map<std::string, sf::Keyboard::Key> keyMap;
};

} // namespace turbohikerSFML
