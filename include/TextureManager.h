#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {
public:
    static void loadTextures();
    static sf::Texture& getShipTexture(int length);
    static sf::Texture& getBoomTexture();

private:
    static std::map<int, sf::Texture> shipTextures;
    static sf::Texture boomTexture;
};
