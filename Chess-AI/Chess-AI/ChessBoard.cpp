#include "ChessBoard.h"

ChessBoard::ChessBoard() : currentPlayer(PlayerColor::White) {
    blackKingTexture.loadFromFile("PNG/Black King.png");
    whiteKingTexture.loadFromFile("PNG/White King.png");
    blackQueenTexture.loadFromFile("PNG/Black Queen.png");
    whiteQueenTexture.loadFromFile("PNG/White Queen.png");
    blackBishopTexture.loadFromFile("PNG/Black Bishop.png");
    whiteBishopTexture.loadFromFile("PNG/White Bishop.png");
    blackKnightTexture.loadFromFile("PNG/Black Knight.png");
    whiteKnightTexture.loadFromFile("PNG/White Knight.png");
    blackRookTexture.loadFromFile("PNG/Black Rook.png");
    whiteRookTexture.loadFromFile("PNG/White Rook.png");
    blackPawnTexture.loadFromFile("PNG/Black Pawn.png");
    whitePawnTexture.loadFromFile("PNG/White Pawn.png");
    initChessBoard();
    loadPieces();
}

void ChessBoard::initChessBoard() {
    // Définie la taille des carrés de 100px
    float squareSize = 100.f;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessBoardSquares[i][j].setSize(sf::Vector2f(squareSize, squareSize));
            // Alterne entre deux couleurs (blanc et gris)
            if ((i + j) % 2 == 0) {
                chessBoardSquares[i][j].setFillColor(sf::Color::White);
            }
            else {
                chessBoardSquares[i][j].setFillColor(sf::Color(128, 128, 128));
            }
            chessBoardSquares[i][j].setPosition(i * squareSize, j * squareSize);
        }
    }
}

void ChessBoard::loadPieces() {
    // Pièces blanches
    // Tour, cavalier, fou, reine, roi, fou, cavalier, tour
    pieces.push_back(Piece(PieceType::Rook, PieceColor::White, whiteRookTexture));     // Tour a1
    pieces.push_back(Piece(PieceType::Knight, PieceColor::White, whiteKnightTexture)); // Cavalier b1
    pieces.push_back(Piece(PieceType::Bishop, PieceColor::White, whiteBishopTexture)); // Fou c1
    pieces.push_back(Piece(PieceType::Queen, PieceColor::White, whiteQueenTexture));   // Reine d1
    pieces.push_back(Piece(PieceType::King, PieceColor::White, whiteKingTexture));     // Roi e1
    pieces.push_back(Piece(PieceType::Bishop, PieceColor::White, whiteBishopTexture)); // Fou f1
    pieces.push_back(Piece(PieceType::Knight, PieceColor::White, whiteKnightTexture)); // Cavalier g1
    pieces.push_back(Piece(PieceType::Rook, PieceColor::White, whiteRookTexture));     // Tour h1

    // Pions blancs
    // Pions sur la rangée 2
    for (int i = 0; i < 8; i++) {
        pieces.push_back(Piece(PieceType::Pawn, PieceColor::White, whitePawnTexture));
        pieces[8 + i].setPosition(i * 100, 100);
    }

    // Set position des pièces blanches (rangée 1)
    pieces[0].setPosition(0 * 100, 0 * 100); // Tour a1
    pieces[1].setPosition(1 * 100, 0 * 100); // Cavalier b1
    pieces[2].setPosition(2 * 100, 0 * 100); // Fou c1
    pieces[3].setPosition(3 * 100, 0 * 100); // Reine d1
    pieces[4].setPosition(4 * 100, 0 * 100); // Roi e1
    pieces[5].setPosition(5 * 100, 0 * 100); // Fou f1
    pieces[6].setPosition(6 * 100, 0 * 100); // Cavalier g1
    pieces[7].setPosition(7 * 100, 0 * 100); // Tour h1

    // Pièces noires
    // Tour, cavalier, fou, reine, roi, fou, cavalier, tour
    pieces.push_back(Piece(PieceType::Rook, PieceColor::Black, blackRookTexture));     // Tour a8
    pieces.push_back(Piece(PieceType::Knight, PieceColor::Black, blackKnightTexture)); // Cavalier b8
    pieces.push_back(Piece(PieceType::Bishop, PieceColor::Black, blackBishopTexture)); // Fou c8
    pieces.push_back(Piece(PieceType::Queen, PieceColor::Black, blackQueenTexture));   // Reine d8
    pieces.push_back(Piece(PieceType::King, PieceColor::Black, blackKingTexture));     // Roi e8
    pieces.push_back(Piece(PieceType::Bishop, PieceColor::Black, blackBishopTexture)); // Fou f8
    pieces.push_back(Piece(PieceType::Knight, PieceColor::Black, blackKnightTexture)); // Cavalier g8
    pieces.push_back(Piece(PieceType::Rook, PieceColor::Black, blackRookTexture));     // Tour h8

    // Pions noirs
    // Pions sur la rangée 7
    for (int i = 0; i < 8; i++) {
        pieces.push_back(Piece(PieceType::Pawn, PieceColor::Black, blackPawnTexture));
        pieces[24 + i].setPosition(i * 100, 6 * 100);
    }

    // Set position des pièces noires (rangée 8)
    pieces[16].setPosition(0 * 100, 7 * 100); // Tour a8
    pieces[17].setPosition(1 * 100, 7 * 100); // Cavalier b8
    pieces[18].setPosition(2 * 100, 7 * 100); // Fou c8
    pieces[19].setPosition(3 * 100, 7 * 100); // Reine d8
    pieces[20].setPosition(4 * 100, 7 * 100); // Roi e8
    pieces[21].setPosition(5 * 100, 7 * 100); // Fou f8
    pieces[22].setPosition(6 * 100, 7 * 100); // Cavalier g8
    pieces[23].setPosition(7 * 100, 7 * 100); // Tour h8
}

void ChessBoard::draw(sf::RenderWindow& window) {
    // Draw le terrain
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            window.draw(chessBoardSquares[i][j]);
        }
    }
    // Draw les pièces
    for (Piece& piece : pieces) {
        piece.draw(window);
    }
}

Piece* ChessBoard::getPieceAt(int x, int y) const {
    for (const Piece& piece : pieces) {
        if (piece.getPosition().x == x * 100 && piece.getPosition().y == y * 100) {
            return const_cast<Piece*>(&piece);
        }
    }
    return nullptr;
}

bool ChessBoard::isOccupied(int x, int y) const {
    for (const Piece& piece : pieces) {
        if (piece.getPosition().x == x * 100 && piece.getPosition().y == y * 100) {
            return true;
        }
    }
    return false;
}

bool ChessBoard::isClearPath(int startX, int startY, int endX, int endY) const {
    if (startX == endX) {  // Mouvement vertical
        int minY = std::min(startY, endY);
        int maxY = std::max(startY, endY);
        for (int y = minY + 1; y < maxY; ++y) {
            if (isOccupied(startX, y)) return false;
        }
    }
    else if (startY == endY) {  // Mouvement horizontal
        int minX = std::min(startX, endX);
        int maxX = std::max(startX, endX);
        for (int x = minX + 1; x < maxX; ++x) {
            if (isOccupied(x, startY)) return false;
        }
    }
    else if (abs(startX - endX) == abs(startY - endY)) {  // Mouvement en diagonale
        int xStep = (endX > startX) ? 1 : -1;
        int yStep = (endY > startY) ? 1 : -1;
        int x = startX + xStep;
        int y = startY + yStep;
        while (x != endX && y != endY) {
            if (isOccupied(x, y)) return false;
            x += xStep;
            y += yStep;
        }
    }
    return true;
}

void ChessBoard::promotePawn(Piece& pawn) {
    // Création d'une nouvelle fenêtre de promotion
    sf::RenderWindow promotionWindow(sf::VideoMode(500, 150), "Promote Pawn");

    int iconSize = 100.f;
    // Création des sprites pour les boutons de promotion
    sf::RectangleShape queenSprite(sf::Vector2f(iconSize, iconSize));
    sf::RectangleShape rookSprite(sf::Vector2f(iconSize, iconSize));
    sf::RectangleShape bishopSprite(sf::Vector2f(iconSize, iconSize));

    // Choisir la texture en fonction de la couleur du pion
    if (pawn.getColor() == PieceColor::White) {
        queenSprite.setTexture(&whiteQueenTexture);
        rookSprite.setTexture(&whiteRookTexture);
        bishopSprite.setTexture(&whiteBishopTexture);
    }
    else {
        queenSprite.setTexture(&blackQueenTexture);
        rookSprite.setTexture(&blackRookTexture);
        bishopSprite.setTexture(&blackBishopTexture);
    }

    // Position des sprites dans la fenêtre
    queenSprite.setPosition(50, 25);
    rookSprite.setPosition(200, 25);
    bishopSprite.setPosition(350, 25);

    // Boucle d'événements pour gérer le choix
    while (promotionWindow.isOpen()) {
        sf::Event event;
        while (promotionWindow.pollEvent(event)) {

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(promotionWindow);
                    if (queenSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        pawn.setType(PieceType::Queen);
                        if (pawn.getColor() == PieceColor::White)
                        {
                            pawn.setTexture(whiteQueenTexture);
                        }else
                            pawn.setTexture(blackQueenTexture);
                        promotionWindow.close();
                    }
                    else if (rookSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        pawn.setType(PieceType::Rook);
                        if (pawn.getColor() == PieceColor::White)
                        {
                            pawn.setTexture(whiteRookTexture);
                        }
                        else
                            pawn.setTexture(blackRookTexture);
                        promotionWindow.close();
                    }
                    else if (bishopSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        pawn.setType(PieceType::Bishop); 
                        if (pawn.getColor() == PieceColor::White)
                        {
                            pawn.setTexture(whiteBishopTexture);
                        }
                        else
                            pawn.setTexture(blackBishopTexture);
                        promotionWindow.close();
                    }
                }
            }
        }

        promotionWindow.clear(sf::Color::White);
        promotionWindow.draw(queenSprite);
        promotionWindow.draw(rookSprite);
        promotionWindow.draw(bishopSprite);
        promotionWindow.display();
    }
}

bool ChessBoard::handleEnPassant(int startX, int startY, int endX, int endY, Piece& piece) {
    // Vérifie si c'est un pion et que le mouvement est en diagonale
    if (piece.getType() == PieceType::Pawn && abs(startX - endX) == 1 && abs(startY - endY) == 1) {
        // Vérifie si le dernier mouvement était un pion qui a avancé de deux cases
        if (lastMove.pieceType == PieceType::Pawn && abs(lastMove.startY - lastMove.endY) == 2) {
            // Vérifie si le pion se trouve à côté du pion adverse et que le mouvement est une prise en passant
            if (lastMove.endX == endX && lastMove.endY == startY) {
                // Capture du pion adverse
                for (auto it = pieces.begin(); it != pieces.end(); ++it) {
                    if (it->getPosition().x == lastMove.endX * 100 && it->getPosition().y == lastMove.endY * 100) {
                        pieces.erase(it);  // Retirer le pion capturé
                        return true;  // Prise en passant réussie
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::movePiece(int startX, int startY, int endX, int endY) {
    for (Piece& piece : pieces) {
        if ((currentPlayer == PlayerColor::White && piece.getColor() == PieceColor::White) ||
            (currentPlayer == PlayerColor::Black && piece.getColor() == PieceColor::Black)) {

            if (piece.getPosition().x == startX * 100 && piece.getPosition().y == startY * 100) {
                if (piece.canMoveTo(startX, startY, endX, endY, *this)) {

                    // Vérifie s'il y a une pièce à la position de destination
                    for (const Piece& otherPiece : pieces) {
                        if (otherPiece.getPosition().x == endX * 100 && otherPiece.getPosition().y == endY * 100) {
                            if (otherPiece.getColor() == piece.getColor()) {
                                return false; // On ne peut pas capturer sa propre pièce
                            }
                        }
                    }

                    // Vérifie si la prise en passant est possible
                    if (piece.getType() == PieceType::Pawn && handleEnPassant(startX, startY, endX, endY, piece)) {
                        piece.setPosition(endX * 100, endY * 100);  // Déplace le pion
                        currentPlayer = (currentPlayer == PlayerColor::White) ? PlayerColor::Black : PlayerColor::White;
                        return true;
                    }

                    // Déplace la pièce normalement
                    piece.setPosition(endX * 100, endY * 100);

                    if (piece.getType() == PieceType::Pawn && (endY == 0 || endY == 7)) {
                        // Appel à la méthode pour gérer la promotion
                        promotePawn(piece);
                    }

                    // Vérifie s'il y a une pièce adverse à capturer
                    for (auto it = pieces.begin(); it != pieces.end();) {
                        if (it->getPosition().x == endX * 100 && it->getPosition().y == endY * 100 && it->getColor() != piece.getColor()) {
                            if (it->getType() == PieceType::King) {
                                exit(0);
                            }
                            it = pieces.erase(it);
                            break;
                        }
                        else {
                            ++it;
                        }
                    }
                    lastMove = { startX, startY, endX, endY, piece.getType(), piece.getColor() };

                    currentPlayer = (currentPlayer == PlayerColor::White) ? PlayerColor::Black : PlayerColor::White;

                    return true;
                }
                return false;
            }
        }
    }
    return false;
}
