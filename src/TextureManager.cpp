#include "TextureManager.h"
#include <iostream>

std::map<int, sf::Texture> TextureManager::shipTextures;
sf::Texture TextureManager::boomTexture;

void TextureManager::loadTextures() {
    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture;
        std::string path = "ship_" + std::to_string(i) + ".png";
        if (!texture.loadFromFile(path)) {
            std::cerr << "Nie udało się załadować: " << path << std::endl;
        }
        shipTextures[i] = texture;
    }

    if (!boomTexture.loadFromFile("boom.png")) {
        std::cerr << "Nie udało się załadować: boom.png" << std::endl;
    }
}

sf::Texture& TextureManager::getShipTexture(int length) {
    return shipTextures.at(length);
}

sf::Texture& TextureManager::getBoomTexture() {
    return boomTexture;
}
