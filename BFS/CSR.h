#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class CSR {
private:
	vector<int> NNZ;
	vector<int> rowOffsets;
	vector<int> columnIndexs;
	int n, quantity_NNZ;
public:
	CSR(string filename) {
		quantity_NNZ = 0;
		n = 0;
		ifstream infile;
		infile.open(filename);
		int row, column;
		while (!infile.eof()) {
			infile >> row >> column;
			set(row, column);
		}
		NNZ.emplace_back(quantity_NNZ);
		int i = rowOffsets.size();
		for (; i <= n; i++)
			rowOffsets.emplace_back(quantity_NNZ);
		infile.close();
		//cout << NNZ.size();
	}

	int at(int row, int column) {
		if (row == column)
			return 0;
		if (row > column) {
			int temp;
			temp = column;
			column = row;
			row = temp;
		}
		//row <= column
		int rowOffset = rowOffsets[row]; //the first element's index of NNZ in row
		int nextRowOffset = rowOffsets[row + 1];
		for (int i = rowOffset; i < nextRowOffset; i++) {
			if (columnIndexs[i] == column) {
				return NNZ[i];
			}
		}
		return 0;
	}

	void set(int row, int column) {
		if (n < column) {
			n = column;
		}
		NNZ.emplace_back(1);
		columnIndexs.emplace_back(column);
		int i = (int)rowOffsets.size();
		for (; i <= row; i++) {
			rowOffsets.emplace_back(quantity_NNZ);
		}
		quantity_NNZ++;
	}

	int getSize() {
		return n;
	}




};