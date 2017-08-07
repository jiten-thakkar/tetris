#ifndef __PIECE_H__
#define __PIECE_H__

#include "board.h"

class Piece {
  private:
    int xpos, ypos;
    int height, width;
    int** shape;
    bool alive;

  public:
    enum pieceType {square, s, z, l, j, bar, t};
    Piece(int _width, int _height, int** _shape):width(_width), height(_height), shape(_shape), alive(true), xpos(-1), ypos(-1){}
    Piece(enum pieceType);
    ~Piece();

    void draw(int xpos, int ypos, Board* board) const;

    void initialDraw(int offset) const;

    //return true if piece still alive
    void move(Board*, Board::dir);

    void rotateRight(Board*);

    inline bool isAlive() const {
      return alive;
    }
    bool detectCollision(int xpos, int ypos, Board* board);
    bool canMove(int xpos, int ypos, Board* board);
    void freeze(int xpos, int ypos, int**);
};

#endif
