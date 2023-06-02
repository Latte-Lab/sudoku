#include <iostream>
#include <random>
#include "sudoku.h"
using namespace std;

int main() {
	Sudoku sodoku;
	sodoku.generateSudoku();
	sodoku.printBoard();
	system("pause");
	return 0;
}