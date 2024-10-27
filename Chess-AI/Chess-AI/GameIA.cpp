#include "ChessBoard.h"
#include "GameIA.h"

GameIA::GameIA() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Game IA");
    ChessBoard chessBoard;

    bool isPlayerTurn = true;  // Variable pour g�rer le tour

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Si c'est le tour du joueur
            if (isPlayerTurn) {
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
                            if (chessBoard.movePiece(startX, startY, endX, endY)) {
                                isPlayerTurn = false;  // Change le tour apr�s un mouvement valide
                            }
                            break;
                        }
                    }
                }
            }
            else {
                chessBoard.aiMove();
                isPlayerTurn = true;
            }
        }

        window.clear();
        chessBoard.draw(window);
        window.display();
    }
}
