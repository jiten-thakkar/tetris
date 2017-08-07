#include <iostream>
#include "piece.h"

Piece::Piece(Piece::pieceType type) {
  alive = true;
  xpos = -1;
  ypos = -1;
  switch(type) {
    case Piece::square:
      height = 2;
      width = 2;
      shape = new int*[height]();
      for(int i=0; i<height; i++) {
        shape[i] = new int[width]();
      }
      for(int i=0; i<height; i++)
        for(int j=0; j<width; j++) {
          shape[i][j] = 1;
        }
      break;
    case Piece::s:
      this->height = 2;
      this->width = 3;
      shape = new int*[height]();
      for(int i=0; i<height; i++) {
        shape[i] = new int[width]();
      }
      shape[0][1] = 1;
      shape[0][0] = 0;
      shape[0][2] = 1;
      shape[1][0] = 1;
      shape[1][1] = 1;
      shape[1][2] = 0;
      break;
    case Piece::z:
      this->height = 2;
      this->width = 3;
      shape = new int*[height]();
      for(int i=0; i<height; i++) {
        shape[i] = new int[width]();
      }
      shape[0][1] = 1;
      shape[0][0] = 1;
      shape[0][2] = 0;
      shape[1][0] = 0;
      shape[1][1] = 1;
      shape[1][2] = 1;
      break;
    case Piece::l:
      this->height = 3;
      this->width = 2;
      shape = new int*[height]();
      for(int i=0; i<height; i++) {
        shape[i] = new int[width]();
      }
      shape[0][1] = 0;
      shape[0][0] = 1;
      shape[1][0] = 1;
      shape[1][1] = 0;
      shape[2][0] = 1;
      shape[2][1] = 1;
      break;
    case Piece::j:
      this->height = 3;
      this->width = 2;
      shape = new int*[height]();
      for(int i=0; i<height; i++) {
        shape[i] = new int[width]();
      }
      shape[0][1] = 1;
      shape[0][0] = 0;
      shape[1][0] = 0;
      shape[1][1] = 1;
      shape[2][0] = 1;
      shape[2][1] = 1;
      break;
    case Piece::bar:
      this->height = 1;
      this->width = 4;
      shape = new int*[height]();
      for(int i=0; i<height; i++) {
        shape[i] = new int[width]();
      }
      shape[0][1] = 1;
      shape[0][0] = 1;
      shape[0][2] = 1;
      shape[0][3] = 1;
      break;
    case Piece::t:
      this->height = 3;
      this->width = 3;
      shape = new int*[height]();
      for(int i=0; i<height; i++) {
        shape[i] = new int[width]();
      }
      shape[0][1] = 1;
      shape[0][0] = 1;
      shape[0][2] = 1;
      shape[1][0] = 0;
      shape[1][1] = 1;
      shape[1][2] = 0;
      shape[2][0] = 0;
      shape[2][1] = 1;
      shape[2][2] = 0;
      break;
    default:
      std::cout << "unknown piece type" << std::endl;
  } 
}

Piece::~Piece() {
  for (int row = 0; row < height; row++) {
    delete[] shape[row];
  }
  delete[] shape;
}

void Piece::draw(int xpos, int ypos, Board* board) const {
  int** b = board->getBoard();
  for(int i=0; i<height; i++)
    for(int j=0; j<width; j++) {
      b[xpos+i][ypos+j] |= shape[i][j];
    }
}

bool Piece::detectCollision(int xpos, int ypos, Board* board) {
  int** b = board->getBoard();
  int height = board->getHeight();
  int width = board->getWidth();
  for(int i=0; i<this->height; i++)
    for(int j=0; j<this->width; j++) {
      if((xpos+i < height && ypos+j < width && b[xpos+i][ypos+j] == 1 && shape[i][j] == 1) ||
          xpos+this->height > height) {
        return true;
      }
    }
  return false;
}

bool Piece::canMove(int xpos, int ypos, Board* board) {
  int** b = board->getBoard();
  if(xpos < 0 || ypos < 0 || xpos-height > board->getHeight() || ypos+width > board->getWidth())
    return false;
  return true;
}

void Piece::freeze(int xpos, int ypos, int** b) {
  for(int i=0; i<height; i++)
    for(int j=0; j<width; j++) {
      b[xpos+i][ypos+j] |= shape[i][j];
    }
}

void Piece::move(Board* board, Board::dir dir) {
  if(xpos == -1 && ypos == -1) {
    xpos = 0;
    ypos = board->getWidth() / 2;
  }
  int newxpos=xpos, newypos=ypos;
  if(dir == Board::left) {
    newypos--;
  } else if(dir == Board::right) {
    newypos++;
  } else if(dir == Board::down) {
    //if(newxpos != 0)
    newxpos++;
  }
  if(canMove(newxpos, newypos, board))
    if(detectCollision(newxpos, newypos, board)) {
      freeze(xpos, ypos, board->getBoard());
      alive = false;
      board->createCopy();
    } else {
      board->createCopy();
      //int** copy = board->getCopy();
      freeze(newxpos, newypos, board->getCopy());
      xpos = newxpos;
      ypos = newypos;
    }
}

void Piece::rotateRight(Board* board) {
  int newheight = width;
  int newwidth = height;
  int** newshape;
  newshape = new int*[newheight]();
  for(int i=0; i<newheight; i++) {
    newshape[i] = new int[newwidth]();
  }

  for(int i=0; i<newheight; i++)
    for(int j=0; j<newwidth; j++) {
      newshape[i][j] = shape[j][i];
    }


  int tempheight = height;
  int tempwidth = width;
  int** tempshape = shape;
  height = newheight;
  width = newwidth;
  shape = newshape;

  if(detectCollision(xpos, ypos, board)) {
    height = tempheight;
    width = tempwidth;
    shape = tempshape;
  } else {
    board->createCopy();
    //int** copy = board->getCopy();
    freeze(xpos, ypos, board->getCopy());
  }
}

void Piece::initialDraw(int offset) const {
  for(int i=0; i<height; i++) {
    for(int j=0; j<offset; j++) {
      std::cout << " ";
    }
    for(int j=0; j<width; j++) {
      if(shape[i][j] == 0)
        std::cout << " ";
      else
        std::cout << "#";
    }
    std::cout << std::endl;
  }
}
