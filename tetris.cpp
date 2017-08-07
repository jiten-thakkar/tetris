#include <iostream>
#include "board.h"
#include "console.h"
#include "input.h"
#include "piece.h"

#define BOARD_WIDTH   20
#define BOARD_HEIGHT  20
#define INITIAL_POS_OFFSET 5

static Piece* currPiece;
int nextPiece=0;

Piece* getNextPiece() {
  Piece* p = new Piece(static_cast<Piece::pieceType>(nextPiece%6));
  nextPiece++;
  return p;
}

int gameLoop(Board* board) {
  Input input;
  currPiece = getNextPiece();
  currPiece->initialDraw(INITIAL_POS_OFFSET);
  while(!board->isGameOver()) {
    if(!currPiece->isAlive()) {
      currPiece = getNextPiece();
      currPiece->initialDraw(INITIAL_POS_OFFSET);
    }
    board->printCopy();
    std::cout << std::endl << std::endl << "Your move: ";
    Input::Key key = input.get();
    switch (key) {
      case Input::LEFT:
        std::cout << "LEFT Pressed" << std::endl;
        currPiece->move(board, Board::left);
        break;
      case Input::RIGHT:
        std::cout << "RIGHT pressed" << std::endl;
        currPiece->move(board, Board::right);
        break;
      case Input::UP:
        std::cout << "UP pressed" << std::endl;
        currPiece->rotateRight(board);
        break;
      case Input::DOWN:
        std::cout << "DOWN pressed" << std::endl;
        currPiece->move(board, Board::down);
        break;
      default:
        std::cout << "???" << std::endl;
        break;
      }
      board->checkLines();
    }
    std::cout << "Game over!" << std::endl;
  }

  int main()
  {
    Console console;
    Board board(BOARD_WIDTH, BOARD_HEIGHT);
    Input input;

    // This example code draws a horizontal bar 4 squares long.
    /*board.set(2, 3, 1);
    board.set(2, 4, 1);
    board.set(2, 5, 1);
    board.set(2, 6, 1);
    board.print();

    Input::Key key = input.get();

    switch (key) {
      case Input::LEFT:
        std::cout << "LEFT" << std::endl;
        break;
      case Input::RIGHT:
        std::cout << "RIGHT" << std::endl;
        break;
      case Input::UP:
        std::cout << "UP" << std::endl;
        break;
      case Input::DOWN:
        std::cout << "DOWN" << std::endl;
        break;
      default:
        std::cout << "???" << std::endl;
        break;
    }*/
    gameLoop(&board);

    return 0;
  }
