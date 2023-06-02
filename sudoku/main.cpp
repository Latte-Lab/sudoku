#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "sudoku.h"
using namespace std;

void writeTxt(string name, string content) {
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
			cout << sudoku.printBoard();
		}
		cout << "Generated " << gameNum << " sudoku boards!" << endl;
	}
	else if (cmd[0] == "-s") {
		// 从文件中读取数独游戏并求解
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
		if (gameNum < 1 || gameNum>10000) {
			cout << "Error: Please input a valid number(1-10000)!" << endl;
		}
		string output = "";
		for (int i = 0; i < gameNum; i++) {
			Sudoku sudoku;
			sudoku.generateSudoku(rand() % 36 + 20);
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