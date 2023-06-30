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

int main(int argc, char* argv[]) {
	// 第0个参数是sudoku.exe！
	if (argc == 1) {
		cout << "Error: Please input a command!" << endl;
		return -1;
	}
	else if (argc == 2) {
		cout << "Error: Please input a valid command!" << endl;
		return -1;
	}
	if (strcmp(argv[1], "-c") == 0) {
		if (argc > 3) {
			cout << "Error: Please input a valid command!" << endl;
			return -1;
		}
		// 生成n个数独终局
		string numStr = argv[2];
		try {
			size_t pos;
			int gameNum = stoi(numStr, &pos);
			if (pos != numStr.length()) {
				throw std::invalid_argument("Error: Please input a valid number! Must be an integer within the range!");
			}
			if (gameNum < 1 || gameNum > 1000000) {
				throw std::out_of_range("Error: Please input a valid number(1-1000000)!");
			}
		}
		catch (const std::invalid_argument& e) {
			cout << e.what() << endl;
			return -1;
		}
		catch (const std::out_of_range& e) {
			cout << e.what() << endl;
			return -1;
		}

		int gameNum = stoi(numStr);

		for (int i = 0; i < gameNum; i++) {
			Sudoku sudoku;
			sudoku.generateBoard();
			cout << "--------" << i << "--------" << endl;
			cout << sudoku.printResult();
		}
		cout << "Generated " << gameNum << " sudoku boards!" << endl;
	}
	else if (strcmp(argv[1], "-s") == 0) {
		if (argc > 3) {
			cout << "Error: Please input a valid command!" << endl;
			return -1;
		}
		// 从文件中读取数独游戏并求解，将答案保存到sudoku.txt中
		string filename;
		string content;
		filename = argv[2];
		// 没有输入的文件
		try {
			ifstream file(filename);
			if (!file.is_open()) {
				throw runtime_error("Error: File " + filename + " does not exist!");
			}
			file.close();
		}
		catch (const exception& e) {
			cout << e.what() << endl;
			return -1;
		}
		try {
			content = readTxt(filename);
			// 检查是否是合法有效的数独游戏
			// --------0--------加上81个数独数字=98
			if (content.length() == 0 || content.length() % 98) {
				throw "Error: Please input a valid txt file!";
			}
		}
		catch (exception e) {	// 异常主要是输入错误的文件名，内容不合法
			cout << "Error: Please input a valid txt file!" << endl;
			return -1;
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
			return -1;
		}
		cout << "Solved " << gameNum << " sudokus to sudoku.txt!" << endl;
	}
	else if (strcmp(argv[1], "-n") == 0) {
		// 生成数独游戏，保存到game.txt中
		int gameNum = 0;
		try {
			size_t pos;
			double num = std::stod(argv[2], &pos);
			if (pos != strlen(argv[2])) {
				throw std::invalid_argument("Error: Please input an integer number within the range!");
			}
			if (std::floor(num) != num) {
				throw std::invalid_argument("Error: Please input an integer number within the range!");
			}
			gameNum = static_cast<int>(num);
		}
		catch (const std::invalid_argument& e) {
			cout << e.what() << endl;
			return -1;
		}
		catch (const std::out_of_range&) {
			cout << "Error: Please input a valid number !" << endl;
			return -1;
		}
		if (gameNum < 1 || gameNum > 10000) {
			cout << "Error: Please input a valid number(1-10000)!" << endl;
			return -1;
		}
		int blankNumLeft = 20, blankNumRight = 55;
		bool unique = false;
		if (argc > 3) {
			if (strcmp(argv[3], "-m") == 0) {
				if (argc < 5) {
					cout << "Error: Please input the level of game!" << endl;
					return -1;
				}

				try {
					size_t pos;
					double level = std::stod(argv[4], &pos);
					if (pos != strlen(argv[4]) || std::floor(level) != level) {
						throw std::invalid_argument("Error: Please input a valid integer for level!");
					}
					int gameLevel = static_cast<int>(level);
					if (gameLevel < 1 || gameLevel > 3) {
						throw std::out_of_range("Error: Please input a valid level(1-3)!");
					}

					// 设置生成游戏的难度
					if (gameLevel == 1) {
						blankNumLeft = 20;
						blankNumRight = 30;
					}
					else if (gameLevel == 2) {
						blankNumLeft = 30;
						blankNumRight = 45;
					}
					else {
						blankNumLeft = 45;
						blankNumRight = 55;
					}
				}
				catch (const std::invalid_argument& e) {
					cout << e.what() << endl;
					return -1;
				}
				catch (const std::out_of_range& e) {
					cout << e.what() << endl;
					return -1;
				}
			}
			else if (strcmp(argv[3], "-r") == 0) {
				if (argc < 5) {
					cout << "Error: Please input the range of blanks!" << endl;
					return -1;
				}

				try {
					string range = argv[4];
					int index = range.find('-');

					int left = std::stoi(range.substr(0, index));
					int right = std::stoi(range.substr(index+1));

					if (left < 20 || left > right || right > 55) {
						throw std::out_of_range("Error: Please input a valid range(20-55)!");
					}

					blankNumLeft = left;
					blankNumRight = right;
				}
				catch (const std::invalid_argument&) {
					cout << "Error: Please input valid integer values for range!" << endl;
					return -1;
				}
				catch (const std::out_of_range& e) {
					cout << e.what() << endl;
					return -1;
				}
			}
			else if (strcmp(argv[3], "-u") == 0) {
				// 设置生成的解唯一
				unique = true;
			}
			else {
				cout << "Error: Please input a valid command!" << endl;
				return -1;
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
		catch (exception&) {
			cout << "Error: Fail to write game.txt!" << endl;
			return -1;
		}

		cout << "Generated " << gameNum << " sudokus to game.txt!" << endl;
		
	}
	else {
		cout << "Error: Please input a valid command!" << endl;
		return -1;
	}
	system("pause");
	return 0;
}

#endif