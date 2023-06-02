﻿#include <iostream>
#include <random>
#include <vector>
#include "sudoku.h"
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

bool Sudoku::trySolve(int index) {
	int row = blankRow[index];
	int col = blankCol[index];
	// 记录要填的位置的所在行、列、块用过的数字
	bool rowUsed[9] = { false };
	bool colUsed[9] = { false };
	bool blockUsed[9] = { false };
	for (int j = 0; j < 9; j++) {
		if (board[row][j] == '0')
			continue;
		rowUsed[board[row][j] - '0' - 1] = true;
	}
	for (int i = 0; i < 9; i++) {
		if (board[i][col] == '0')
			continue;
		colUsed[board[i][col] - '0' - 1] = true;
	}
	for (int i = row / 3 * 3; i < row / 3 * 3 + 3; i++)
		for (int j = col / 3 * 3; j < col / 3 * 3 + 3; j++) {
			if (board[i][j] == '0')
				continue;
			blockUsed[board[i][j] - '0' - 1] = true;
		}
	vector<int> possibleNum;	// 可能填入的数字
	for (int i = 0; i < 9; i++) {
		if (!rowUsed[i] && !colUsed[i] && !blockUsed[i]) {
			possibleNum.push_back(i);
			break;
		}
	}
	// 无满足数独规则的可填入的数字，求解失败
	if (possibleNum.size() == 0)
		return false;
	for (int i = 0; i < possibleNum.size(); i++) {
		result[row][col] = possibleNum[i] + '1';
		// 所有空都填入成功
		if ((index + 1) == blankRow.size()) {
			solution++;
			return true;
		}
		// 继续填入下一个，如果下一个没有可以填入的，撤回这一个填入的数字
		if (!trySolve(++index)) {
			result[row][col] = '0';
		}
		else
			return true;
	}
	return false;	// 所有可能的数字都试过后，求解失败
}

void Sudoku::generateBoard() {
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

	// 先保存完整的答案
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			result[i][j] = board[i][j];
}

void Sudoku::generateSudoku(int blankNum) {
	// 生成一个符合数独规则的完整棋盘
	generateBoard();

	// 挖掉blankNum个空
	while (blankNum) {
		int x = rand() % 9;
		int y = rand() % 9;
		if (board[x][y] == '0')
			continue;
		char temp = board[x][y];
		board[x][y] = '0';
		blankRow.push_back(x);
		blankCol.push_back(y);
		solveSudoku();
		// 挖空后尝试求解，若有解则合法，无解则重新填上该空
		if (solution)
			blankNum--;
		else {
			board[x][y] = temp;
			blankRow.pop_back();
			blankCol.pop_back();
		}
	}
}

void Sudoku::solveSudoku() {
	solution = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			result[i][j] = board[i][j];
	// 回溯算法求解数独
	trySolve(0);
}

string Sudoku::printBoard() {
	string out = "";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == '0')
				out.append("  ");
			else {
				out += board[i][j];
				out.append(" ");
			}
		}
		out.append("\n");
	}
	return out;
}

string Sudoku::printResult() {
	string out = "";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			out += result[i][j];
			out.append(" ");
		}
		out.append("\n");
	}
	return out;
}


