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
        return false; // Si la position de d�part et d'arriv�e est la m�me
    }

    switch (type) {
    case PieceType::King:
        return abs(endX - startX) <= 1 && abs(endY - startY) <= 1;  // D�placement d'une case autour du roi
    case PieceType::Queen:
        return (startX == endX || startY == endY) || (abs(startX - endX) == abs(startY - endY)); // D�placement en ligne ou en diagonale (reine)
    case PieceType::Rook:
        return startX == endX || startY == endY; // La tour se d�place en ligne droite
    case PieceType::Bishop:
        return abs(startX - endX) == abs(startY - endY); // Le fou se d�place en diagonale
    case PieceType::Knight:
        return (abs(startX - endX) == 2 && abs(startY - endY) == 1) || (abs(startX - endX) == 1 && abs(startY - endY) == 2); // Le cavalier se d�place en "L"
    case PieceType::Pawn:
        if (color == PieceColor::White) {
            if (startY == 1 && endY == startY + 2 && startX == endX) return true;  // Premier coup du pion blanc
            return endY == startY + 1 && startX == endX;
        }
        else {
            if (startY == 6 && endY == startY - 2 && startX == endX) return true;  // Premier coup du pion noir
            return endY == startY - 1 && startX == endX;
        }
    case PieceType::None:  // Ajout du cas "None"
        return false;  // Aucune pi�ce ne peut se d�placer
    default:
        return false;  // S�curit� suppl�mentaire pour les cas non g�r�s
    }
}
