#ifndef SUDOKU_H 
#define SUDOKU_H
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "sudoku.h"
using namespace std;

string readTxt(const string name) {
	ifstream is;
	is.open(name, ios::in);
	string content;
	while (!is.eof()) {
		// 逐字符读取
		// --------0--------7065980...70859--------1--------
		char c;
		is >> c;
		content += c;
	}
	is.close();
	content = content.substr(0, content.length() - 1);
	return content;
}

void writeTxt(const string name, const string content) {
	ofstream os;
	os.open(name, ios::out);
	os << content;
	os.close();
}

int main() {
	string str;
	getline(cin, str);
	vector<string> cmd;
	istringstream in(str);
	while (in >> str) {
		cmd.push_back(str);
	}
	if (cmd.size() == 0) {
		cout << "Error: Please input a command!" << endl;
		return 0;
	}
	if (cmd[0] == "-c") {
		// 生成n个数独终局
		int gameNum = 0;
		try {
			gameNum = atoi(cmd[1].c_str());
		}
		catch (exception e) {	// 异常主要是没有输入n或者输入的非整数
			cout << "Error: Please input the number of game!" << endl;
		}
		if (gameNum < 1 || gameNum>1000000) {
			cout << "Error: Please input a valid number(1-1000000)!" << endl;
		}
		for (int i = 0; i < gameNum; i++) {
			Sudoku sudoku;
			sudoku.generateBoard();
			cout << "--------" << i << "--------" << endl;
			cout << sudoku.printResult();
		}
		cout << "Generated " << gameNum << " sudoku boards!" << endl;
	}
	else if (cmd[0] == "-s") {
		// 从文件中读取数独游戏并求解，将答案保存到sudoku.txt中
		string filename;
		string content;
		try {
			filename = cmd[1];
			content = readTxt(filename);
			// 检查是否是合法有效的数独游戏
			// --------0--------加上81个数独数字=98
			if (content.length() == 0 || content.length() % 98) {
				throw "Error: Please input a valid txt file!";
			}
		}
		catch (exception e) {	// 异常主要是没有输入或输入错误的文件名，内容不合法
			cout << "Error: Please input a valid txt file!" << endl;
		}
		int gameNum = static_cast<int>(content.length() / 98);
		string answer = "";
		for (int i = 0; i < gameNum; i++) {
			Sudoku sudoku;
			sudoku.setBoard(content.substr(static_cast<size_t>(i) * 98 + 17, 81));
			sudoku.solveSudoku();
			answer.append("--------");
			answer.append(to_string(i));
			answer.append("--------\n");
			answer.append(sudoku.printResult());
		}
		try {
			writeTxt("sudoku.txt", answer);
		}
		catch (exception e) {
			cout << "Error: Fail to write sudoku.txt!" << endl;
		}
		cout << "Solved " << gameNum << " sudokus to sudoku.txt!" << endl;
	}
	else if (cmd[0] == "-n") {
		// 生成数独游戏，保存到game.txt中
		int gameNum = 0;
		try {
			gameNum = atoi(cmd[1].c_str());
		}
		catch (exception e) {	// 异常主要是没有输入n或者输入的非整数
			cout << "Error: Please input the number of game!" << endl;
		}
		if (gameNum < 1 || gameNum > 10000) {
			cout << "Error: Please input a valid number(1-10000)!" << endl;
		}
		int blankNumLeft = 20, blankNumRight = 55;
		bool unique = false;
		if (cmd.size() > 2) {
			if (cmd[2] == "-m") {
				// 设置生成游戏的难度
				int level = 0;
				try {
					level = atoi(cmd[3].c_str());
				}
				catch (exception e) {	// 异常主要是没有输入或者输入的非整数
					cout << "Error: Please input the level of game!" << endl;
				}
				if (level < 1 || level > 3) {
					cout << "Error: Please input a valid level(1-3)!" << endl;
				}
				// 难度越高，挖空越多
				if (level == 1) {
					blankNumLeft = 20;
					blankNumRight = 30;
				}
				else if (level == 2) {
					blankNumLeft = 30;
					blankNumRight = 45;
				}
				else {
					blankNumLeft = 45;
					blankNumRight = 55;
				}
			}
			else if (cmd[2] == "-r") {
				// 设置挖空范围
				string range;
				try {
					int index = static_cast<int>(cmd[3].find("-"));
					blankNumLeft = atoi(cmd[3].substr(0, index).c_str());
					blankNumRight = atoi(cmd[3].substr(static_cast<size_t>(index) + 1, cmd[3].length()).c_str());
					if (blankNumLeft<20 || blankNumLeft>blankNumRight || blankNumRight > 55) {
						throw "Error: Please input a valid range(20-55)!";
					}
				}
				catch (exception e) {	// 异常主要是没有输入或者输入的非整数范围
					cout << "Error: Please input the range of blanks!" << endl;
				}
			}
			else if (cmd[2] == "-u") {
				// 设置生成的解唯一
				unique = true;
			}
		}
		string output = "";
		for (int i = 0; i < gameNum; i++) {
			Sudoku sudoku;
			sudoku.generateSudoku(rand() % (blankNumRight - blankNumLeft + 1) + blankNumLeft, unique);
			output.append("--------");
			output.append(to_string(i));
			output.append("--------\n");
			output.append(sudoku.printBoard());
		}
		try {
			writeTxt("game.txt", output);
		}
		catch (exception e) {
			cout << "Error: Fail to write game.txt!" << endl;
		}
		cout << "Generated " << gameNum << " sudokus to game.txt!" << endl;
	}
	system("pause");
	return 0;
}

#endif