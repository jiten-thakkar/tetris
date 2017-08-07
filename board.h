#ifndef __BOARD_H__
#define __BOARD_H__

// Board represents the Tetris board and has methods for accessing and printing
// the board state.
class Board {
private:
	int** board;
  int** copy;
  int width;
  int height;
  int score;

public:
	Board(int width, int height);
	~Board();
	void set(int row, int col, int value);
	int get(int row, int col) const;
	void print();
	void printCopy();
  void checkLines();
  bool isGameOver() const;

  inline int getHeight() const {return height;}

  inline int getWidth() const {return width;}

  inline int** getBoard() {return board;}

  inline int** getCopy() const {return copy;};

  void createCopy();

  void clearCopy();

  enum dir {up, down, left, right};
};

#endif /* __BOARD_H__ */
