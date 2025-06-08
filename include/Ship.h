#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Ship {
protected:
    int length;
    bool horizontal;
    sf::Vector2i position;
    std::vector<bool> hits;

public:
    Ship(int length, sf::Vector2i pos, bool horizontal);
    virtual ~Ship() = default;

    virtual void draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const = 0;

    int getLength() const;
    sf::Vector2i getPosition() const;
    bool isHorizontal() const;
    bool isSunk() const;

    bool occupies(sf::Vector2i cell) const;
    void hitAt(sf::Vector2i cell);
};
