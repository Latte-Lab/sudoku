#include <iostream>
#include <random>
#include "sudoku.h"
using namespace std;

int main() {
	Sudoku sodoku;
	sodoku.generateSudoku(20);
	system("pause");
	return 0;
}