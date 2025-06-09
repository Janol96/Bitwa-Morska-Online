#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <cmath>
#include "SinglePlayerScreen.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 500;
const std::string MENU_TEXTURE_PATH = "menu_bg_clear.png";

void drawMenu(sf::RenderWindow& window, sf::Font& font, sf::Texture* bgTexture,
              std::vector<sf::Text>& options, int hovered, sf::Text& titleText) {
    window.clear();

    if (bgTexture) {
        sf::Sprite bg(*bgTexture);
        bg.setScale(
            static_cast<float>(WINDOW_WIDTH) / bg.getTexture()->getSize().x,
            static_cast<float>(WINDOW_HEIGHT) / bg.getTexture()->getSize().y
            );
        window.draw(bg);
    }

    window.draw(titleText);

    for (size_t i = 0; i < options.size(); ++i) {
        options[i].setFillColor(i == hovered ? sf::Color::Yellow : sf::Color(20, 40, 60));
        window.draw(options[i]);
    }

    window.display();
}

void drawFontError(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    sf::Font defaultFont;
    if (defaultFont.loadFromFile("arial.ttf")) {
        sf::Text errorText("Blad: Nie mozna zaladowac czcionki.", defaultFont, 24);
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(200, 200);
        window.draw(errorText);
    }
    window.display();
    sf::sleep(sf::seconds(3));
}

int main() {
    std::cout << "Current working dir: " << std::filesystem::current_path() << std::endl;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bitwa Morska Online");

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        std::cerr << "Blad: nie mozna zaladowac czcionki Roboto-Regular.ttf" << std::endl;
        drawFontError(window);
        return -1;
    }

    sf::Texture menuTexture;
    bool menuBgLoaded = menuTexture.loadFromFile(MENU_TEXTURE_PATH);
    if (!menuBgLoaded) {
        std::cerr << "Uwaga: nie zaladowano tła menu (" << MENU_TEXTURE_PATH << ")\n";
    }

    sf::Clock clock;

    std::vector<sf::Text> menuOptions;
    std::vector<std::string> labels = {
        "1. TRYB JEDNOOSOBOWY",
        "2. GRA ONLINE",
        "3. USTAWIENIA",
        "4. WYJSCIE"
    };
    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text(labels[i], font, 36);
        text.setPosition(300, 150 + static_cast<int>(i) * 60);
        text.setFillColor(sf::Color(20, 40, 60));
        menuOptions.push_back(text);
    }

    sf::Text titleText("BITWA MORSKA ONLINE", font, 60);
    titleText.setFillColor(sf::Color(20, 40, 60));
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
    titleText.setPosition(WINDOW_WIDTH / 2, 60);

    int hoveredIndex = -1;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        float scale = 1.0f + 0.05f * std::sin(time * 2);
        titleText.setScale(scale, scale);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        hoveredIndex = -1;
        for (size_t i = 0; i < menuOptions.size(); ++i) {
            if (menuOptions[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                hoveredIndex = static_cast<int>(i);
                break;
            }
        }

        drawMenu(window, font, menuBgLoaded ? &menuTexture : nullptr, menuOptions, hoveredIndex, titleText);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed &&
                       event.mouseButton.button == sf::Mouse::Left && hoveredIndex != -1) {

                if (hoveredIndex == 0) {
                    // TRYB JEDNOOSOBOWY
                    SinglePlayerScreen singlePlayer(font);
                    singlePlayer.run(window);
                } else if (hoveredIndex == 3) {
                    window.close();
                }
            }
        }
    }

    return 0;
}
