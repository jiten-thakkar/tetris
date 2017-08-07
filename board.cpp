#include <iostream>
#include "board.h"

Board::Board(int width, int height)
{
	this->width = width;
	this->height = height;
	board = new int*[height]();
	for (int row = 0; row < height; row++) {
		board[row] = new int[width]();
	}
  copy = NULL;
  createCopy();
  score = 0;
}

void Board::createCopy() {
  if(copy != NULL)
    clearCopy();
  copy = new int*[height]();
	for (int row = 0; row < height; row++) {
		copy[row] = new int[width]();
	}
  for(int i=0; i<height; i++)
    for(int j=0; j<width; j++) {
      copy[i][j] = board[i][j];
    }
}

void Board::clearCopy() {
	for (int row = 0; row < height; row++) {
		delete[] copy[row];
	}
	delete[] copy;
}

Board::~Board()
{
	for (int row = 0; row < height; row++) {
		delete[] board[row];
	}
	delete[] board;
}

void Board::set(int row, int col, int value)
{
	board[row][col] = value;
}

int Board::get(int row, int col) const
{
	return board[row][col];
}

void Board::printCopy()
{
	for (int col = 0; col < width+2; col++) {
		std::cout << "-";
	}

	std::cout << std::endl;
	for (int row = 0; row < height; row++) {
		std::cout << "|";
		for (int col = 0; col < width; col++) {
			std::cout << (copy[row][col] == 0 ? ' ' : '#');
		}
		std::cout << "|" << std::endl;
	}

	for (int col = 0; col < width+2; col++) {
		std::cout << "-";
	}

	std::cout << std::endl;
  std::cout << "Score: " << score << std::endl;
}

void Board::print()
{
	for (int col = 0; col < width+2; col++) {
		std::cout << "-";
	}

	std::cout << std::endl;
	for (int row = 0; row < height; row++) {
		std::cout << "|";
		for (int col = 0; col < width; col++) {
			std::cout << (board[row][col] == 0 ? ' ' : '#');
		}
		std::cout << "|" << std::endl;
	}

	for (int col = 0; col < width+2; col++) {
		std::cout << "-";
	}

	std::cout << std::endl;
  std::cout << "Score: " << score << std::endl;
}

bool Board::isGameOver() const {
  for(int j=0; j<width; j++) {
    if(board[0][j])
      return true;
  }
  return false;
}

void Board::checkLines() {
  for(int i=height-1; i>=0; i--) {
    bool packed = true;
    for(int j=0; j<width; j++) {
      if(board[i][j] == 0) {
        packed = false;
        break;
      }
    }
    if(packed) {
      score++;
      for(int j=i-1; j>=0; j--) {
        for(int z=0; z<width; z++) {
          board[j+1][z] = board[j][z];
        }
      }
      for(int j=0; j<width; j++)
        board[0][j] = 0;
      createCopy();
      i++;
    }
  }
}
