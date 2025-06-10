#include "AIPlayer.h"
#include "BasicShip.h"
#include <cstdlib>
#include <ctime>
#include <memory>

AIPlayer::AIPlayer(const std::string& name)
    : Player(name)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void AIPlayer::placeShipsRandomly() {
    std::vector<int> shipSizes = {4, 3, 2, 1};
    for (int size : shipSizes) {
        bool placed = false;
        while (!placed) {
            int x = std::rand() % 10;
            int y = std::rand() % 10;
            bool horizontal = std::rand() % 2;

            auto ship = std::make_shared<BasicShip>(size, sf::Vector2i(x, y), horizontal);
            placed = getBoard().addShip(ship);
        }
    }
}

sf::Vector2i AIPlayer::chooseShot() {
    sf::Vector2i shot;
    do {
        shot = sf::Vector2i(std::rand() % 10, std::rand() % 10);
    } while (shotsFired.count({shot.x, shot.y}) > 0);

    shotsFired.insert({shot.x, shot.y});
    return shot;
}
