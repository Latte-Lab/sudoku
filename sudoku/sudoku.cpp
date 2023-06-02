#include "sudoku.h"
#include <iostream>
#include <random>
using namespace std;

void Sudoku::transform(int x, int y, bool isRow) {
	if (isRow) {
		// 左边行变换
		for (int i = x; i < (x + 3); i++) {
			for (int j = y; j < (y + 3); j++) {
				if (i % 3 == 0)
					board[i][j] = board[i + 2][j + 3];
				else
					board[i][j] = board[i - 1][j + 3];
			}
		}
		// 左边行变换
		for (int i = x; i < (x + 3); i++) {
			for (int j = y + 6; j < (y + 9); j++) {
				if ((i + 1) % 3 == 0)
					board[i][j] = board[i - 2][j - 3];
				else
					board[i][j] = board[i + 1][j - 3];
			}
		}
	}
	else {
		// 上面列变换
		for (int i = x; i < (x + 3); i++) {
			for (int j = y; j < (y + 3); j++) {
				if (j % 3 == 0)
					board[i][j] = board[i + 3][j + 2];
				else
					board[i][j] = board[i + 3][j - 1];
			}
		}
		// 下面列变换
		for (int i = (x + 6); i < (x + 9); i++) {
			for (int j = y; j < (y + 3); j++) {
				if ((j + 1) % 3 == 0)
					board[i][j] = board[i - 3][j - 2];
				else
					board[i][j] = board[i - 3][j + 1];
			}
		}
	}
}

void Sudoku::generateSudoku() {
	// 生成一个符合数独规则的完整棋盘
	// 在最中间的一大格随机生成不重复的9个数字
	bool middle[9] = { false };			// 表示9个数字是否被使用过了
	for (int i = 3; i < 6; i++) {
		for (int j = 3; j < 6; j++) {
			int temp = rand() % 9;
			while (middle[temp])
				temp = (temp + 1) % 9;
			middle[temp] = true;
			board[i][j] = temp + '1';	// 注意这里是加'1'，因为取余的范围在0-8
		}
	}
	// 将最中间的一大格向周围做矩阵变换
	transform(3, 0, true);
	transform(0, 3, false);
	transform(0, 0, true);
	transform(6, 0, true);
}

void Sudoku::printBoard() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
}
