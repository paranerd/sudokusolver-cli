#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

vector< vector<int> > grid;
vector< vector<int> > tempGrid;

void printGrid() {

	cout << endl << "Solved:" << endl;
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			cout << tempGrid[i][j];
			if(j < 6 && (j + 1) % 3 == 0) {
				cout << "|";
			}
		}
		if(i < 6 && (i + 1) % 3 == 0) {
			cout << endl << "-----------";
		}
		cout << endl;
	}
}

void loadGrid(bool crack) {
	cout << "Enter the grid:" << endl;
	for(int i = 0; i < 9; i++) {
		string line;
		if(crack) {
			while(line.length() != 9) {
				cout << i << ": ";
				getline(cin, line);
				if(line.length() == 0) {
					line = "000000000";
					break;
				}
			}
		}
		vector<int> row;
		for(int j = 0; j < 9; j++) {
			if(crack) {
				int number = atoi(line.substr(j, 1).c_str());
				row.push_back(number);
			}
			else {
				row.push_back(0);
			}
		}
		grid.push_back(row);
	}

	// Fill temporary grid
	for(int i = 0; i < 9; i++) {
		vector<int> tempRow;
		for(int j = 0; j < 9; j++) {
			int number = grid[i][j];
			tempRow.push_back(number);
		}
		tempGrid.push_back(tempRow);
	}
	//printGrid();
}

bool conflicts(int number, int row, int col) {
	if(number == 0) {
		return true;
	}

	// Horizontal || Vertical || Box
	for(int i = 0; i < 9; i++) {
		if(	i != col && tempGrid[row][i] == number ||
			i != row && tempGrid[i][col] == number ||
			((row - row % 3) + i / 3) != row && ((col - col % 3) + i % 3) != col && tempGrid[(row - row % 3) + i / 3][(col - col % 3) + i % 3] == number) {
			return true;
		}
	}
	return false;
}

time_t start = time(0);
int elapsed = 0;
int counter = 0;
int counterPerSec = 0;

void solve() {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			while(conflicts(tempGrid[i][j], i, j)) {
				bool done = false;
				while(tempGrid[i][j] == 9) {
					tempGrid[i][j] = 0;
					if(j == 0) {
						j = 8;
						i--;
					}
					else {
						j--;
					}
					if(i < 0) {
						cout << "No solution!" << endl;
					}
					done = true;
					if(tempGrid[i][j] < 9 && grid[i][j] == 0) {
						tempGrid[i][j]++;
					}
					counter++;
					counterPerSec++;
				}
				if(!done) {
					tempGrid[i][j]++;
				}
				time_t now = time(0);
				if(now - start > 1) {
					elapsed++;
					cout << elapsed << "s | " << counterPerSec << "/s | " << counter << endl;
					start = time(0);
					counterPerSec = 0;
				}
			}
		}
	}
	printGrid();
}

int main(int argc, char* argv[]) {
	bool mode = false;
	if(argc > 1 && (string) argv[1] == "-c") {
		mode = true;
	}
	loadGrid(mode);
	solve();
	return 0;
}
