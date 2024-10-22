#include "ChessBoard.h"

ChessBoard::ChessBoard() {
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

bool ChessBoard::isOccupied(int x, int y) const {
    for (const Piece& piece : pieces) {
        if (piece.getPosition().x == x * 100 && piece.getPosition().y == y * 100) {
            return true;
        }
    }
    return false;
}

bool ChessBoard::movePiece(int startX, int startY, int endX, int endY) {
    for (Piece& piece : pieces) {
        if (piece.getPosition().x == startX * 100 && piece.getPosition().y == startY * 100) {
            if (piece.canMoveTo(startX, startY, endX, endY, *this)) {

                // Vérification s'il y a une pièce adverse à capturer
                for (auto it = pieces.begin(); it != pieces.end(); ++it) {
                    if (it->getPosition().x == endX * 100 && it->getPosition().y == endY * 100 && it->getColor() != piece.getColor()) {
                        pieces.erase(it);  // Capturer la pièce adverse
                        break;
                    }
                }

                // Déplacer la pièce
                piece.setPosition(endX * 100, endY * 100);
                return true;
            }
            return false;
        }
    }
    return false;
}