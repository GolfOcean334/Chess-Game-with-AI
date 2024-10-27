#include "Piece.h"
#include "ChessBoard.h"

Piece::Piece() : type(PieceType::None), color(Color::None) {}

Piece::Piece(PieceType type, Color  color, const sf::Texture& texture) : type(type), color(color) {
    sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    float scaleX = 100.0f / textureSize.x;
    float scaleY = 100.0f / textureSize.y;
    sprite.setScale(scaleX, scaleY);
}

void Piece::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Piece::setType(PieceType newType) {
    type = newType;
}

void Piece::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Piece::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

PieceType Piece::getType() const {
    return type;
}

Color Piece::getColor() const {
    return color;
}

sf::Vector2f Piece::getPosition() const {
    return sprite.getPosition();
}

int Piece::getPieceValue(PieceType type) {
    switch (type) {
    case PieceType::Pawn: return 1;
    case PieceType::Knight: return 3;
    case PieceType::Bishop: return 3;
    case PieceType::Rook: return 5;
    case PieceType::Queen: return 9;
    case PieceType::King: return 1000;
    default: return 0;
    }
}

bool Piece::canMoveTo(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    if (startX == endX && startY == endY) {
        return false;
    }

    switch (type) {
    case PieceType::King:
        // Déplacement d'une case autour du roi ou tentative de roque
        if (abs(endX - startX) <= 1 && abs(endY - startY) <= 1) {
            return true;
        }
        // Tentative de roque
        if (abs(endX - startX) == 2 && startY == endY) {
            return board.handleCastling(startX, startY, endX, endY, *this) != nullptr;
        }
        return false;
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
        // Le cavalier se déplace en "L"
        return (abs(startX - endX) == 2 && abs(startY - endY) == 1) || (abs(startX - endX) == 1 && abs(startY - endY) == 2);
    case PieceType::Pawn:
        if (color == Color::Black) {
            if (startY == 1 && endY == startY + 2 && startX == endX && !board.isOccupied(endX, endY) && !board.isOccupied(endX, endY - 1)) {
                return true;  // Premier coup du pion blanc
            }
            if (endY == startY + 1 && startX == endX && !board.isOccupied(endX, endY)) {
                return true;  // Mouvement de base
            }
            if (endY == startY + 1 && abs(startX - endX) == 1 && board.isOccupied(endX, endY) && board.getPieceAt(endX, endY)->getColor() != this->color) {
                return true;  // Capture en diagonale
            }
            // Prise en passant
            if (abs(startX - endX) == 1 && startY + 1 == endY) {
                return board.handleEnPassant(startX, startY, endX, endY, *const_cast<Piece*>(this));
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
            // Prise en passant
            if (abs(startX - endX) == 1 && startY - 1 == endY) {
                return board.handleEnPassant(startX, startY, endX, endY, *const_cast<Piece*>(this));
            }
        }
        return false;
    case PieceType::None:
        return false;
    default:
        return false;
    }
}
