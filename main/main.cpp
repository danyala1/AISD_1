#include <iostream>
#include <clocale>
#include <conio.h>
using namespace std;
class Three {
	struct Leaves {
		int value;
		Leaves* Left = nullptr;
		Leaves* Right = nullptr;
	};
	Leaves* root = new Leaves;
	Leaves* rec_erase(Leaves* elem, int key) {
		if (elem == NULL) return elem;
		else if (key < elem->value) elem->Left = rec_erase(elem->Left, key);
		else if (key > elem->value) elem->Right = rec_erase(elem->Right, key);
		else {
			// Case 1:  No child
			if (elem->Left == NULL && elem->Right == NULL) {
				delete elem;
				elem = NULL;
			}
			//Case 2: One child 
			else if (elem->Left == NULL) {
				struct Leaves* temp = elem;
				elem = elem->Right;
				delete temp;
			}
			else if (elem->Right == NULL) {
				struct Leaves* tmp = elem;
				elem = elem->Left;
				delete tmp;
			}
			// case 3: 2 children
			else {
				struct Leaves* tmp = FindMin(elem->Right);
				elem->value = tmp->value;
				elem->Right = rec_erase(elem->Right, tmp->value);
			}
		}
		return elem;
	}
	bool rec_insert(Leaves* elem, int key) {

		if (elem == nullptr || key == elem->value) return false;
		if (key > elem->value) {
			if (elem->Right)
			{
				return rec_insert(elem->Right, key);
			}
			else {
				Leaves* tmp = new Leaves;
				elem->Right = tmp;
				tmp->value = key;

			}
		}
		else if (key < elem->value) {
			if (elem->Left) {
				return rec_insert(elem->Left, key);
			}
			else {
				Leaves* tmp = new Leaves;
				elem->Left = tmp;
				tmp->value = key;

			}
		}
		return true;

	}