#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include "Color.h"

class ChessBoard;

enum class PieceType { None, King, Queen, Rook, Bishop, Knight, Pawn };

class Piece {
public:
    Piece();
    Piece(PieceType type, Color color, const sf::Texture& texture);

    void setPosition(float x, float y);
    void setType(PieceType newType);
    void setTexture(const sf::Texture& texture);

    void draw(sf::RenderWindow& window);

    PieceType getType() const;
    Color getColor() const;

    sf::Vector2f getPosition() const;

    static int getPieceValue(PieceType type);

    bool canMoveTo(int startX, int startY, int endX, int endY, const ChessBoard& board) const;

private:
    PieceType type;
    Color color;
    sf::Sprite sprite;
};

#endif
