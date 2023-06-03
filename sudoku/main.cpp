#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "sudoku.h"
using namespace std;

string readTxt(string name) {
	ifstream is;
	is.open(name, ios::in);
	string content;
	while (!is.eof()) {
		// ���ַ���ȡ
		// --------0--------7065980...70859--------1--------
		char c;
		is >> c;
		content += c;
	}
	is.close();
	content = content.substr(0, content.length() - 1);
	return content;
}

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
		// ����n�������վ�
		int gameNum = 0;
		try {
			gameNum = atoi(cmd[1].c_str());
		}
		catch (exception e) {	// �쳣��Ҫ��û������n��������ķ�����
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
		// ���ļ��ж�ȡ������Ϸ����⣬���𰸱��浽sudoku.txt��
		string filename;
		string content;
		try {
			filename = cmd[1];
			content = readTxt(filename);
			// ����Ƿ��ǺϷ���Ч��������Ϸ
			// --------0--------����81����������=98
			if (content.length() == 0 || content.length() % 98) {
				throw "Error: Please input a valid txt file!";
			}
		}
		catch (exception e) {	// �쳣��Ҫ��û����������������ļ��������ݲ��Ϸ�
			cout << "Error: Please input a valid txt file!" << endl;
		}
		int gameNum = content.length() / 98;
		string answer = ""; 
		for (int i = 0; i < gameNum; i++) {
			Sudoku sudoku;
			sudoku.setBoard(content.substr(i * 98 + 17, 81));
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
		// ����������Ϸ�����浽game.txt��
		int gameNum = 0;
		try {
			gameNum = atoi(cmd[1].c_str());
		}
		catch (exception e) {	// �쳣��Ҫ��û������n��������ķ�����
			cout << "Error: Please input the number of game!" << endl;
		}
		if (gameNum < 1 || gameNum > 10000) {
			cout << "Error: Please input a valid number(1-10000)!" << endl;
		}
		int blankNumLeft = 20, blankNumRight = 55;
		bool unique = false;
		if (cmd.size() > 2) {
			if (cmd[2] == "-m") {
				// ����������Ϸ���Ѷ�
				int level = 0;
				try {
					level = atoi(cmd[3].c_str());
				}
				catch (exception e) {	// �쳣��Ҫ��û�������������ķ�����
					cout << "Error: Please input the level of game!" << endl;
				}
				if (level < 1 || level > 3) {
					cout << "Error: Please input a valid level(1-3)!" << endl;
				}
				// �Ѷ�Խ�ߣ��ڿ�Խ��
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
				// �����ڿշ�Χ
				string range;
				try {
					int index = cmd[3].find("-");
					blankNumLeft = atoi(cmd[3].substr(0, index).c_str());
					blankNumRight = atoi(cmd[3].substr(index + 1, cmd[3].length()).c_str());
					if (blankNumLeft<20 || blankNumLeft>blankNumRight || blankNumRight > 55) {
						throw "Error: Please input a valid range(20-55)!";
					}
				}
				catch (exception e) {	// �쳣��Ҫ��û�������������ķ�������Χ
					cout << "Error: Please input the range of blanks!" << endl;
				}
			}
			else if (cmd[2] == "-u") {
				// �������ɵĽ�Ψһ
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