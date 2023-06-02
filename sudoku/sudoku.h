#pragma once
#include <vector>
using namespace std;

class Sudoku {
private:
	vector<int> blankRow;
	vector<int> blankCol;
	int solution = 0;
	char board[9][9] = { '0' };
	char result[9][9] = { '0' };
	void transform(int x, int y, bool isRow);
	bool trySolve(int index);
public:
	void generateBoard();
	void generateSudoku(int blankNum);
	void solveSudoku();
	string printBoard();
	string printResult();
};
