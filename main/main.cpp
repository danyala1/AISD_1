#include <iostream>
#include <clocale>
#include <conio.h>
#include <vector>
#include <ctime>
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
	Leaves* rec_contains(Leaves* elem, int key) {
		//if (elem == nullptr) return 0;
		//if (elem->value == key) return 1;
		//if (elem->value > key) return rec_contains(elem->Right, key);
		//else return rec_contains(elem->Left, key);
		if (elem != NULL && elem->value != key)
		{
			if (key < elem->value) elem = rec_contains(elem->Left, key);
			else elem = rec_contains(elem->Right, key);
		}
		return elem;
	}
	void rec_print(Leaves* elem)
	{
		if (elem != nullptr) {
			if (elem->Left)rec_print(elem->Left);
			cout << elem->value << ' ';
			if (elem->Right)rec_print(elem->Right);
		}
	}
	void clear(Leaves*& elem)
	{
		if (elem)
		{
			clear(elem->Left);
			clear(elem->Right);
			delete elem;
			elem = NULL;
		}

	}
	void copy(Leaves*& first, const Leaves* second)
	{
		if (!second)
		{
			first = NULL;
			return;
		}
		first = new Leaves;
		first->value = second->value;
		copy(first->Left, second->Left);
		copy(first->Right, second->Right);
	}
	Leaves* FindMin(Leaves* elem) {
		if (elem->Left) {
			return FindMin(elem->Left);
		}
		return elem;
	}
public:
	Three(Three& src) {
		root = NULL;
		copy(root, src.root);
	}
	~Three() { clear(root); }
	Three(int key) {
		//Leaves* root = new Leaves;
		root->value = key;
	}
	void print() {
		rec_print(this->root);
	}

	Three& operator=(const Three& src)
	{
		if (this == (&src)) { return *this; }
		clear(root);
		copy(root, src.root);
		return *this;
	}
	bool insert(int key) {
		return rec_insert(this->root, key);

	}//вставка элемента
	bool contains(int key) {
		if (rec_contains(this->root, key)) return true;
		return false;
	} //проверка наличи€ элемента

	int Find() {

		return (FindMin(this->root))->value;
	}
	void erase(int key) {
		rec_erase(this->root, key);

	} //удаление элемента
};
size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

float TestFirst(int value) {

	//дл€ 100 раз
	//ќтсечь  врем€
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	//остановить врем€
	//врем€ добавить в вектор

	//сумму вектора времени делим на 100 и возвращаем
	return 1;
}
float TestSecond(int value) {

	//дл€ 1000 раз
	//ќтсечь  врем€
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.contains(lcg());
	}
	//остановить врем€
	//врем€ добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}

float TestThird(int value) {

	//дл€ 1000 раз
	//ќтсечь  врем€
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	for (int i = 0; i < value - 1; i++)
	{
		B.erase(lcg());
	}
	//остановить врем€
	//врем€ добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}
float TestVectorFirst(int value) {

	vector<double> TimeVector(value);
	//дл€ 100 раз
	clock_t t0 = clock();
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	clock_t t1 = clock();//остановить врем€
	//врем€ добавить в вектор
	cout << (double)(t1 - t0) / CLOCKS_PER_SEC;
	TimeVector.push_back((double)(t1 - t0) / CLOCKS_PER_SEC);
	//сумму вектора времени делим на 100 и возвращаем
	return 1;
}
float TestVectorSecond(int value) {

	//дл€ 1000 раз
	//ќтсечь  врем€
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.contains(lcg());
	}
	//остановить врем€
	//врем€ добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}

float TestVectorThird(int value) {

	//дл€ 1000 раз
	//ќтсечь  врем€
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	for (int i = 0; i < value - 1; i++)
	{
		B.erase(lcg());
	}
	//остановить врем€
	//врем€ добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}