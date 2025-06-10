#include "Player.h"

Player::Player(Board& board, sf::Font& font)
    : board(board), font(font), name("Gracz") {}

Player::Player(const std::string& name)
    : name(name), board(10), font(*new sf::Font()) {}


Board& Player::getBoard() {
    return board;
}

const Board& Player::getBoard() const {
    return board;
}

void Player::addShip(std::shared_ptr<Ship> ship) {
    board.addShip(ship);
}

std::vector<std::shared_ptr<Ship>> Player::getShips() const {
    return board.getShips();
}
