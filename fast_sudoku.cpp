#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

void printGrid(char** tGrid, int stepsCount) {

	cout << endl << "Solved after " << stepsCount << " steps." << endl;
	for(int i = 0; i < 9; i++) {
			cout << tGrid[i] << endl;
	}
}

char** loadGrid() {
	char** table = new char*[9];
	cout << "Enter the grid" << endl << "End row with [Return]" << endl << "Free spaces with dots (.)" << endl;
	for(int i = 0; i < 9; i++) {
		string line;
		getline(cin, line);
		for(int j = 0; j < 9; j++) {
			table[i] = new char[line.size()];
			//line.copy(table[0], line.size());
			strcpy(table[i], line.c_str());
			if(table[i][j] < '0' || table[i][j] > '9') {
				table[i][j] = '.';
			}
		}
	}

	return table;
}

char* getCandidates(char** tGrid, int row, int col) {
	cout << "Called with: " << row << ", " << col << endl;
	string s = "";

	for(char c = '1'; c <= '9'; c++) {
		bool collision = false;
		for(int i = 0; i < 9; i++) {
			int test = (row - row % 3) + i / 3;
			cout << "Test " << test << endl;
			if(tGrid[row][i] == c ||
			   tGrid[i][col] == c ||
			   tGrid[(row - row % 3) + i / 3][(col - col % 3) + i % 3] == c) {
				collision = true;
				break;
			}
		}
		if(!collision) {
			s += c;
		}
	}
	cout << s << endl;
	char* theReturn = new char[s.size()];
	strcpy(theReturn, s.c_str());
	return theReturn;
}

bool solve(char** tGrid, int stepsCount) {
	bool solved = false;

	int row = -1;
	int col = -1;
	char* candidates;

	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(tGrid[i][j] == '.') {
				char* newCandidates = getCandidates(tGrid, i, j);
				cout << "New: " << newCandidates << endl;
				if(row < 0 || strlen(newCandidates) < strlen(candidates)) {
					row = i;
					col = j;
					candidates = newCandidates;
				}
			}
		}
	}
	if(row < 0) {
		solved = true;
	}
	else {
		for(int i = 0; i < strlen(candidates); i++) {
			tGrid[row][col] = candidates[i];
			stepsCount++;
			if(solve(tGrid, stepsCount)) {
				solved = true;
				break;
			}
			tGrid[row][col] = '.';
		}
	}
	return solved;
}

int main(int argc, char* argv[]) {
	int stepsCount = 0;
	char** tGrid = loadGrid();
	if(solve(tGrid, stepsCount)) {
		printGrid(tGrid, stepsCount);
	}
	else {
		cout << "Could not solve this Sudoku.";
	}
	return 0;
}
