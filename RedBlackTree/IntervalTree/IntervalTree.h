#pragma once
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

enum Color { RED, BLACK };

typedef struct s_interval {
	int low;
	int high;
}Interval;

typedef struct ITNode
{
	Color color;
	int key;
	int size;
	int max;
	Interval interval;
	struct ITNode* left;
	struct ITNode* right;
	struct ITNode* p;
}ITNode, * ITree;

ITree NIL;

void UpdateInfo(ITree x);

void Left_Rotate(ITree& T, ITree x);
void Right_Rotate(ITree& T, ITree x);
ITree TreeSuccessor(ITree z);

ITree DeleteITree(ITree& T, ITree z);
void DeleteITree_Fixup(ITree& T, ITree x);

void InsertITree(ITree& T, ITree z);
void InsertITree_Fixup(ITree& T, ITree z);

void InitCreateITree(ITree& T, vector<Interval>& num);
ITree IntervalSearch(ITree T, Interval i);
ITree FindNodeByRank(ITree T, int rank);
bool isOverlap(Interval x, Interval i);


bool isOverlap(Interval x, Interval i) {
	if (i.high < x.low || x.high < i.low)
		return false;
	else
		return true;
}

void UpdateInfo(ITree x) {
	x->size = x->left->size + x->right->size + 1;
	x->max = max(x->interval.high, max(x->left->max, x->right->max));
}

void Left_Rotate(ITree& T, ITree x) {
	ITree y;
	y = x->right;
	x->right = y->left;
	if (y->left != NIL)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NIL)
		T = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;

	//update max and size; x is son of y
	UpdateInfo(x);
	UpdateInfo(y);

}

void Right_Rotate(ITree& T, ITree x) {
	ITree y;
	y = x->left;
	x->left = y->right;
	if (y->right != NIL)
		y->right->p = x;
	y->p = x->p;
	if (x->p == NIL)
		T = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->right = x;
	x->p = y;

	//update max and size; x is son of y
	UpdateInfo(x);
	UpdateInfo(y);


}

ITree TreeSuccessor(ITree z) { //assume right tree not NIL
	ITree y = z->right;
	while (y->left != NIL) {
		y = y->left;
	}
	return y;
}

ITree DeleteITree(ITree& T, ITree z) {
	ITree x, y;
	if (z->left == NIL || z->right == NIL)
		y = z;
	else
		y = TreeSuccessor(z);
	if (y->left != NIL)
		x = y->left;
	else
		x = y->right; //include case  3
	x->p = y->p;
	if (y->p == NIL)
		T = x;
	else
	{
		if (y == y->p->left)
			y->p->left = x;
		else
			y->p->right = x;
	}
	if (y != z) {
		int temp;
		Interval temp_Int;
		temp = z->key;
		z->key = y->key;
		y->key = temp;
		temp_Int = z->interval;
		z->interval = y->interval;
		y->interval = temp_Int;
	}



	//update max and size
	z = y->p;
	while (z != NIL)
	{
		UpdateInfo(z);
		z = z->p;
	}
	//update max and size

	if (y->color == BLACK)
		DeleteITree_Fixup(T, x);
	return y; //remmber to delete y
}

void DeleteITree_Fixup(ITree& T, ITree x) {
	ITree w;
	while (x != NIL && x->color == BLACK)
	{
		if (x == x->p->left) { //
			w = x->p->right;
			if (w->color == RED) { //case 1 
				w->color = BLACK;
				x->p->color = RED;
				Left_Rotate(T, x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) { ///case2 
				w->color = RED;
				x = x->p;
			}
			else { //case 1 -> case 3 or 4
				if (w->right->color == BLACK) { //case 3
					w->left->color = BLACK;
					w->color = RED;
					Right_Rotate(T, w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				Left_Rotate(T, x->p);
				x = T;
			}
		}
		else { //
			w = x->p->left;
			if (w->color == RED) { //case 1 
				w->color = BLACK;
				x->p->color = RED;
				Right_Rotate(T, x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) { ///case2 
				w->color = RED;
				x = x->p;
			}
			else { //case 1 -> case 3 or 4
				if (w->left->color == BLACK) { //case 3
					w->right->color = BLACK;
					w->color = RED;
					Left_Rotate(T, w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				Right_Rotate(T, x->p);
				x = T;
			}
		}
	}
	x->color = BLACK;
}

void InsertITree(ITree& T, ITree z) {
	ITree y;
	ITree x;
	y = NIL;
	x = T;
	while (x != NIL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == NIL)
		T = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;


	// update max and size
	z->size = 1;
	z->max = z->interval.high;
	y = z->p;
	while (y != NIL)
	{
		UpdateInfo(y);
		y = y->p;
	}
	//update max and size

	z->left = NIL;
	z->right = NIL;
	z->color = RED;
	InsertITree_Fixup(T, z);
}

void InsertITree_Fixup(ITree& T, ITree z) {
	ITree y;
	while (z->p->color == RED) {  //??? may z->p = NIL?
		if (z->p == z->p->p->left) { //case 1 2 3
			y = z->p->p->right;
			if (y->color == RED) { //case 1
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else // case 2 3
			{
				if (z == z->p->right) //case 2
				{
					z = z->p;
					Left_Rotate(T, z);
				}
				//case 3:
				z->p->color = BLACK;
				z->p->p->color = RED;
				Right_Rotate(T, z->p->p);
			}

		}
		else { //case 4 5 6
			y = z->p->p->left;
			if (y->color == RED) { //case 1
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else // case 2 3
			{
				if (z == z->p->left) //case 2
				{
					z = z->p;
					Right_Rotate(T, z);
				}
				//case 3:
				z->p->color = BLACK;
				z->p->p->color = RED;
				Left_Rotate(T, z->p->p);
			}

		}
	}//end while
	T->color = BLACK;
}

ITree IntervalSearch(ITree T, Interval i) {
	ITree x = T;
	while (x != NIL && !isOverlap(x->interval, i))
	{
		if (x->left != NIL && x->left->max >= i.low)
			x = x->left;
		else
			x = x->right;
	}
	return x;

}

void InitCreateITree(ITree& T, vector<Interval>& num) {
	ITree p;
	NIL = new ITNode;
	NIL->size = 0;
	NIL->left = NIL;
	NIL->right = NIL;
	NIL->color = BLACK;
	NIL->interval.high = 0;
	NIL->interval.low = 0;
	NIL->max = 0;
	T = NIL;
	for (auto elem : num) {
		p = new ITNode;
		p->key = elem.low;
		p->interval = elem;
		p->p = NIL;
		p->left = NIL;
		p->right = NIL;
		p->max = p->interval.high;
		p->size = 1;
		InsertITree(T, p);
	}
	T->p = NIL;
}


//void SetSize(ITree T) {
//
//	if (T != NIL) {
//		SetSize(T->left);
//		SetSize(T->right);
//		T->size = T->left->size + T->right->size + 1;
//	}
//}

ITree FindNodeByRank(ITree T, int rank) {
	//SetSize(T);
	if (rank > T->size || rank < 1)
		return NIL;
	else {

		if (rank <= T->left->size)
			return FindNodeByRank(T->left, rank);
		else if (rank == T->left->size + 1)
			return T;
		else
			return FindNodeByRank(T->right, rank - T->left->size - 1);
	}
}

