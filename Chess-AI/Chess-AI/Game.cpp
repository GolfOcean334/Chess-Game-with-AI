#include "ChessBoard.h"
#include "Game.h"

Game::Game() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Game");

    ChessBoard chessBoard;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gestion de la souris pour d�placer une pi�ce
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int startX = event.mouseButton.x / 100;
                int startY = event.mouseButton.y / 100;

                // Attendre que l'utilisateur clique sur la destination
                while (window.waitEvent(event)) {
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        int endX = event.mouseButton.x / 100;
                        int endY = event.mouseButton.y / 100;

                        // D�placer la pi�ce
                        chessBoard.movePiece(startX, startY, endX, endY);
                        break;
                    }
                }
            }
        }
        window.clear();
        chessBoard.draw(window);
        window.display();
    }
}