#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Ship.h"

class NetworkManager {
private:
    bool isServer;
    sf::TcpSocket socket;
    sf::TcpListener listener;

public:
    NetworkManager();

    bool startServer(unsigned short port);
    bool startClient(const std::string& ip, unsigned short port);

    bool sendMessage(const std::string& message);
    bool receiveMessage(std::string& message);

    bool sendBoard(const std::vector<std::shared_ptr<Ship>>& ships);
    bool receiveBoard(std::vector<std::shared_ptr<Ship>>& shipsOut);

    bool sendShot(const sf::Vector2i& pos);
    bool receiveShot(sf::Vector2i& posOut);

    bool sendShotResult(bool hit);
    bool receiveShotResult(bool& hitOut);

};
