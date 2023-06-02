#pragma once

class Sudoku {
private:
	char board[9][9] = { '0' };
	char result[9][9] = { '0' };
	void transform(int x, int y, bool isRow);
public:
	void generateSudoku();
	void printBoard();
};
