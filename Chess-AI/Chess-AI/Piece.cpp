#include "Piece.h"
#include "ChessBoard.h"

Piece::Piece() : type(PieceType::None), color(PieceColor::None) {}

Piece::Piece(PieceType type, PieceColor color, const sf::Texture& texture)
    : type(type), color(color) {
    sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    float scaleX = 100.0f / textureSize.x;
    float scaleY = 100.0f / textureSize.y;
    sprite.setScale(scaleX, scaleY);
}

void Piece::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Piece::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

PieceType Piece::getType() const {
    return type;
}

PieceColor Piece::getColor() const {
    return color;
}

sf::Vector2f Piece::getPosition() const {
    return sprite.getPosition();
}

bool Piece::canMoveTo(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    if (startX == endX && startY == endY) {
        return false;
    }

    switch (type) {
    case PieceType::King:
        return abs(endX - startX) <= 1 && abs(endY - startY) <= 1;  // Déplacement d'une case autour du roi
    case PieceType::Queen:
        // Mouvement comme une tour
        if (startX == endX || startY == endY) {
            return board.isClearPath(startX, startY, endX, endY);
        }
        // Mouvement comme un fou
        else if (abs(startX - endX) == abs(startY - endY)) {
            return board.isClearPath(startX, startY, endX, endY);
        }
        return false;
    case PieceType::Rook:
        // Mouvement vertical et horizontal
        if (startX == endX || startY == endY) {
            return board.isClearPath(startX, startY, endX, endY);
        }
        return false;
    case PieceType::Bishop:
        // Mouvement en diagonal
        if (abs(startX - endX) == abs(startY - endY)) {
            return board.isClearPath(startX, startY, endX, endY);
        }
        return false;
    case PieceType::Knight:
        return (abs(startX - endX) == 2 && abs(startY - endY) == 1) || (abs(startX - endX) == 1 && abs(startY - endY) == 2); // Le cavalier se déplace en "L"
    case PieceType::Pawn:
        if (color == PieceColor::White) {
            if (startY == 1 && endY == startY + 2 && startX == endX && !board.isOccupied(endX, endY) && !board.isOccupied(endX, endY - 1)) {
                return true;  // Premier coup du pion blanc
            }
            if (endY == startY + 1 && startX == endX && !board.isOccupied(endX, endY)) {
                return true;  // Mouvement de base
            }
            if (endY == startY + 1 && abs(startX - endX) == 1 && board.isOccupied(endX, endY) && board.getPieceAt(endX, endY)->getColor() != this->color) {
                return true;  // Capture en diagonale
            }
        }
        else {
            if (startY == 6 && endY == startY - 2 && startX == endX && !board.isOccupied(endX, endY) && !board.isOccupied(endX, endY + 1)) {
                return true;  // Premier coup du pion noir
            }
            if (endY == startY - 1 && startX == endX && !board.isOccupied(endX, endY)) {
                return true;  // Mouvement de base
            }
            if (endY == startY - 1 && abs(startX - endX) == 1 && board.isOccupied(endX, endY) && board.getPieceAt(endX, endY)->getColor() != this->color) {
                return true;  // Capture en diagonale
            }
        }
        return false;
    case PieceType::None:
        return false;
    default:
        return false;
    }
}
