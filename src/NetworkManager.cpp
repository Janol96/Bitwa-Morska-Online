#include "NetworkManager.h"
#include "BasicShip.h"

#include <iostream>

NetworkManager::NetworkManager() {
    socket.setBlocking(true);
    listener.setBlocking(true);
}

bool NetworkManager::startServer(unsigned short port) {
    isServer = true;
    if (listener.listen(port) != sf::Socket::Done) {
        std::cerr << "[Server] Błąd nasłuchu na porcie " << port << std::endl;
        return false;
    }

    std::cout << "[Server] Oczekiwanie na klienta..." << std::endl;
    if (listener.accept(socket) != sf::Socket::Done) {
        std::cerr << "[Server] Błąd przy akceptowaniu połączenia!" << std::endl;
        return false;
    }

    std::cout << "[Server] Połączenie ustanowione!" << std::endl;
    return true;
}

bool NetworkManager::startClient(const std::string& ip, unsigned short port) {
    isServer = false;
    if (socket.connect(ip, port) != sf::Socket::Done) {
        std::cerr << "[Client] Nie udało się połączyć z serwerem!" << std::endl;
        return false;
    }

    std::cout << "[Client] Połączono z serwerem!" << std::endl;
    return true;
}

bool NetworkManager::sendMessage(const std::string& message) {
    sf::Packet packet;
    packet << message;
    return socket.send(packet) == sf::Socket::Done;
}

bool NetworkManager::receiveMessage(std::string& message) {
    sf::Packet packet;
    if (socket.receive(packet) != sf::Socket::Done)
        return false;

    packet >> message;
    return true;
}

bool NetworkManager::sendBoard(const std::vector<std::shared_ptr<Ship>>& ships) {
    sf::Packet packet;
    packet << static_cast<sf::Uint32>(ships.size());

    for (const auto& ship : ships) {
        packet << ship->getPosition().x
               << ship->getPosition().y
               << static_cast<sf::Uint32>(ship->isHorizontal() ? 1 : 0)
               << static_cast<sf::Uint32>(ship->getLength());
    }

    return socket.send(packet) == sf::Socket::Done;
}

bool NetworkManager::receiveBoard(std::vector<std::shared_ptr<Ship>>& shipsOut) {
    sf::Packet packet;
    if (socket.receive(packet) != sf::Socket::Done)
        return false;

    sf::Uint32 count;
    packet >> count;

    for (sf::Uint32 i = 0; i < count; ++i) {
        int x, y, isHor, length;
        packet >> x >> y >> isHor >> length;

        auto ship = std::make_shared<BasicShip>(length, sf::Vector2i(x, y), isHor == 1);
        shipsOut.push_back(ship);
    }

    return true;
}

// 🔫 Strzały – pozycja
bool NetworkManager::sendShot(const sf::Vector2i& pos) {
    sf::Packet packet;
    packet << pos.x << pos.y;
    return socket.send(packet) == sf::Socket::Done;
}

bool NetworkManager::receiveShot(sf::Vector2i& posOut) {
    sf::Packet packet;
    if (socket.receive(packet) != sf::Socket::Done)
        return false;

    int x, y;
    packet >> x >> y;
    posOut = sf::Vector2i(x, y);
    return true;
}

//Wynik strzału (trafienie/pudło)
bool NetworkManager::sendShotResult(bool hit) {
    sf::Packet packet;
    packet << static_cast<sf::Uint32>(hit ? 1 : 0);
    return socket.send(packet) == sf::Socket::Done;
}

bool NetworkManager::receiveShotResult(bool& hitOut) {
    sf::Packet packet;
    if (socket.receive(packet) != sf::Socket::Done)
        return false;

    sf::Uint32 result;
    packet >> result;
    hitOut = (result == 1);
    return true;
}
