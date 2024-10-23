#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

class ChessBoard;

enum class PieceType { None, King, Queen, Rook, Bishop, Knight, Pawn };
enum class PieceColor { White, Black, None };

class Piece {
public:
    Piece();
    Piece(PieceType type, PieceColor color, const sf::Texture& texture);

    void setPosition(float x, float y);
    void setType(PieceType newType);
    void setTexture(const sf::Texture& texture);

    void draw(sf::RenderWindow& window);

    PieceType getType() const;
    PieceColor getColor() const;

    sf::Vector2f getPosition() const;

    bool canMoveTo(int startX, int startY, int endX, int endY, const ChessBoard& board) const;

private:
    PieceType type;
    PieceColor color;
    sf::Sprite sprite;
};

#endif
