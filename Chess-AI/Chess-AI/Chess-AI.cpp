#include <SFML/Graphics.hpp>
#include "GamePvP.h"
#include "GameIA.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "Choisissez votre mode de jeu");

    sf::Font font;
    if (!font.loadFromFile("Font/SophiaFrancesca.ttf")) {
        return -1;
    }

    sf::Text textPvP("Jouer contre un joueur", font, 20);
    textPvP.setPosition(100, 50);
    textPvP.setFillColor(sf::Color::White);

    sf::Text textIA("Jouer contre l'IA", font, 20);
    textIA.setPosition(100, 120);
    textIA.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (textPvP.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    GamePvP::GamePvP();
                    window.close();
                }
                else if (textIA.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    GameIA::GameIA();
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(textPvP);
        window.draw(textIA);
        window.display();
    }

    return 0;
}
