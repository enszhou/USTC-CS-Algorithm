#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "IntervalTree.h"


#define BUFFER_SIZE 150

using namespace std;
char colors[2][10] = { "RED", "BLACK" };
int NIL_NUM = 0;


void Print(ITree T, ITree pT, ofstream& outfile) {
	if (T != NIL) {
		char s1[BUFFER_SIZE];
		snprintf(s1, BUFFER_SIZE, "x%p[label=\"[%d, %d]\nmax = %d\",color=\"%s\"];\nx%p -> x%p;\n", T, T->interval.low, T->interval.high, T->max, colors[T->color], T->p, T);
		outfile << s1;
		Print(T->left, T, outfile);
		Print(T->right, T, outfile);
	}
	else {
		char s2[BUFFER_SIZE];
		snprintf(s2, BUFFER_SIZE, "NIL%d[color=\"BLACK\"];\nx%p -> NIL%d;\n", NIL_NUM, pT, NIL_NUM);
		outfile << s2;
		NIL_NUM++;
	}
	return;
}

void PrintITree(ITree T, const char* filename) {
	ofstream outfile;
	char s1[BUFFER_SIZE];
	snprintf(s1, BUFFER_SIZE, "../%s.dot", filename);
	//outfile.open("ITree.dot", ios::out | ios::trunc);
	outfile.open(s1, ios::out | ios::trunc);
	string clause;


	clause = "digraph ITree{\n node[shape=\"circle\", fontcolor=\"white\", style=\"filled\"];\n  ";
	outfile << clause;

	if (T != NIL) {
		char s2[BUFFER_SIZE];
		snprintf(s2, BUFFER_SIZE, "x%p[label=\"[%d, %d]\nmax = %d\", color=\"%s\"];\n", T, T->interval.low, T->interval.high, T->max, colors[T->color]);
		outfile << s2;
		Print(T->left, T, outfile);
		Print(T->right, T, outfile);
	}
	else {
		char s3[BUFFER_SIZE];
		snprintf(s3, BUFFER_SIZE, "NIL%d[color=\"BLACK\"];\n", NIL_NUM++);
		outfile << s3;
	}

	clause = "}";
	outfile << clause;
	outfile.close();
	char s4[BUFFER_SIZE];
	snprintf(s4, BUFFER_SIZE, "dot ../%s.dot | gvpr -c -f binarytree.gvpr | neato -n -Tsvg -o ../%s.svg", filename, filename);
	system(s4);
}


int main()
{
	int n;
	cin >> n;
	//n = 20;
	int r1, r2;
	vector<Interval> num(n);
	for (int i = 0; i < n; i++) {
		r1 = rand() * 500 / RAND_MAX;
		r2 = rand() * 500 / RAND_MAX;
		num[i].low = r1 < r2 ? r1 : r2;
		num[i].high = r1 + r2 - num[i].low;
		cout << "[" << num[i].low << "," << num[i].high << "] ";
	}
	cout << endl;
	ITree T;
	InitCreateITree(T, num);

	//print ITree
	PrintITree(T, "ITree_Init\0");
	cout << "Create ITree successfully!" << endl;

	//delete 
	ITree y;
	ITree half = FindNodeByRank(T, n / 2);
	y = DeleteITree(T, half);
	cout << "delete [" << y->interval.low << "," << y->interval.high << "]" << endl;
	delete y;
	ITree quarter = FindNodeByRank(T, n / 4);
	y = DeleteITree(T, quarter);
	cout << "delete [" << y->interval.low << "," << y->interval.high << "]" << endl;
	delete y;

	//print ITree
	NIL_NUM = 0;
	PrintITree(T, "ITree_AfterDelete\0");
	cout << "Create ITree after being deleted successfully!" << endl;
}

