#pragma once
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <vector>

struct LastMove {
    int startX, startY, endX, endY;
    PieceType pieceType;
    PieceColor pieceColor;
};

class ChessBoard {
public:
    enum class PlayerColor { White, Black };
    PlayerColor currentPlayer;
    LastMove lastMove;

    ChessBoard();
    void initChessBoard();
    void loadPieces();
    void draw(sf::RenderWindow& window);

    Piece* getPieceAt(int x, int y) const;

    bool isOccupied(int x, int y)const;
    bool isClearPath(int startX, int startY, int endX, int endY) const;

    void promotePawn(Piece& piece);
    const Piece* handleEnPassant(int startX, int startY, int endX, int endY, const Piece& piece) const;
    const Piece* handleCastling(int startX, int startY, int endX, int endY, const Piece& piece) const;

    ChessBoard clone() const;
    int evaluateBoard() const;
    int evaluateBestMove(int depth);

    void aiMove();
    bool movePiece(int startX, int startY, int endX, int endY);

private:
    sf::RectangleShape chessBoardSquares[8][8];
    std::vector<Piece> pieces;

    sf::Texture blackKingTexture;
    sf::Texture whiteKingTexture;
    sf::Texture blackQueenTexture;
    sf::Texture whiteQueenTexture;
    sf::Texture blackBishopTexture;
    sf::Texture whiteBishopTexture;
    sf::Texture blackKnightTexture;
    sf::Texture whiteKnightTexture;
    sf::Texture blackRookTexture;
    sf::Texture whiteRookTexture;
    sf::Texture blackPawnTexture;
    sf::Texture whitePawnTexture;
};

#endif
