#pragma once
#include <vector>
using namespace std;

class Sudoku {
private:
	vector<int> blankRow;
	vector<int> blankCol;
	int solution = 0;
	bool unique = false;
	char board[9][9] = { '$' };
	char midResult[9][9] = { '$' };
	char finalResult[9][9] = { '$' };
	void transform(int x, int y, bool isRow);
	bool trySolve(int index);
public:
	void setBoard(string str);
	void generateBoard();
	void generateSudoku(int blankNum, bool unique);
	void solveSudoku();
	string printBoard();
	string printResult();
};
