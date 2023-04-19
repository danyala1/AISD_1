#include <iostream>
# include <clocale>
#include <conio.h>
#include<vector>

using namespace std;
class Three {
	struct Leaves {
		int value;
		Leaves* Left = nullptr;
		Leaves* Right = nullptr;
	};
	int count = 0;
	int height = 0;
	Leaves* root = new Leaves;
	Leaves* rec_erase(Leaves* elem, int key) {
		if (elem == NULL) return elem;
		else if (key < elem->value) elem->Left = rec_erase(elem->Left, key);
		else if (key > elem->value) elem->Right = rec_erase(elem->Right, key);
		else {
			if (elem->Left == NULL && elem->Right == NULL) {
				delete elem;
				elem = NULL;
			}
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

			else {
				struct Leaves* tmp = FindMin(elem->Right);
				elem->value = tmp->value;
				elem->Right = rec_erase(elem->Right, tmp->value);
			}
			this->count--;

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
				this->height++;
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
				this->height++;
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
	void rec_print(Leaves* root, int ident, int level) const
	{
		if (root)
		{
			rec_print(root->Left, -1, level + 2);
			for (int i = 0; i < level; i++) cout << "   ";
			if (ident == 0)
				cout << root->value << "----------------------------------" << endl;
			if (ident == 1)
				cout << root->value << endl;
			if (ident == -1)
				cout << root->value << endl;
			rec_print(root->Right, 1, level + 2);
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
		this->count = src.count;
	}
	~Three() {
		clear(root); this->count = 0; this->height = 0;
	}
	Three(int key) {
		//Leaves* root = new Leaves;
		root->value = key;
		this->count = 1;
		this->height = 1;
	}
	void print() {
		rec_print(this->root, 1, this->height);
	}

	Three& operator=(const Three& src)
	{
		if (this == (&src)) { return *this; }
		clear(root);
		copy(root, src.root);
		this->count = src.count;
		return *this;
	}
	bool insert(int key) {

		bool tmp = rec_insert(this->root, key);
		if (tmp) this->count++;
		return tmp;

	}//вставка элемента
	bool contains(int key) {
		if (rec_contains(this->root, key)) return true;
		return false;
	} //проверка наличия элемента

	int FindM() {
		if (this->count == 0) {
			std::cout << "Нет элементов";
			return 0;
		}
		else return (FindMin(this->root))->value;
	}
	bool erase(int key) {
		this->root = rec_erase(this->root, key);
		return true;
		//--------------------------------------------------------------
	} //удаление элемента
};


size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
#include <chrono>
using namespace std::chrono;


double TestFirstHelp(int value, bool Is_Vector)
{
	if (!Is_Vector) {
		//Отсечь  время
		auto start = high_resolution_clock::now();
		Three B(lcg());
		for (int i = 0; i < value - 1; i++) B.insert(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		return (double)duration.count();
	}
	vector<int> TimeVector(value);
	//для 100 раз
	auto start = high_resolution_clock::now();
	for (int i = 0; i < value - 1; i++)  TimeVector.push_back(lcg());
	auto stop = high_resolution_clock::now();
	chrono::duration<double> duration = stop - start;
	return(double)duration.count();
}
double TestSecondHelp(int value, bool Is_Vector) {
	if (!Is_Vector) {
		Three B(lcg());
		for (int j = 0; j < value; j++) B.insert(lcg());
		auto start = high_resolution_clock::now();
		B.contains(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		return (double)duration.count();
	}
	vector<int> TimeVector(value);
	for (int i = 0; i < value; i++)TimeVector.push_back(lcg());
	auto start = high_resolution_clock::now();
	find(TimeVector.begin(), TimeVector.end(), lcg());    //erase(lcg());
	auto stop = high_resolution_clock::now();
	chrono::duration<double> duration = stop - start;
	return (double)duration.count();


}
double TestThirdHelp(int value, bool Is_Vector = true)
{
	if (!Is_Vector) {
		Three B(lcg());
		for (int i = 0; i < value - 1; i++)B.insert(lcg());
		auto start = high_resolution_clock::now();
		B.insert(lcg());
		B.erase(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		return (double)duration.count();
	}


}
double TestFirst(int value) {
	double sum = 0;

	//для 100 раз
	for (int j = 0; j < 100; j++) {

		sum += TestFirstHelp(value, false);
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 100 и возвращаем
	return sum / 100;
}
double TestSecond(int value) {
	double  sum = 0;
	//для 1000 раз
	//Отсечь  время
	for (int j = 0; j < 1000; j++) {
		sum += TestSecondHelp(value, false);
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем

	return sum / 1000;
}
double TestThird(int value) {

	double  sum = 0;
	//для 1000 раз
	//Отсечь  время
	for (int j = 0; j < 1000; j++) {
		sum += TestThirdHelp(value);
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return sum / 1000;
}

double TestVectorFirst(int value) {

	double sum = 0;
	//время добавить в вектор
	for (int j = 0; j < 100; j++) {

		sum += TestFirstHelp(value, true);
	}
	//сумму вектора времени делим на 100 и возвращаем
	return sum / 100;
}
double TestVectorSecond(int value) {

	//для 1000 раз
	//Отсечь  время

	double sum = 0;
	for (int j = 0; j < 1000; j++) {

		sum += TestSecondHelp(value, true);

	}
	//остановить время


	//сумму вектора времени делим на 1000 и возвращаем
	return sum / 1000;
}
double TestVectorThird(int value) {
	vector<int> TimeVector(value);
	//для 1000 раз
	//Отсечь  время
	double sum = 0;
	for (int i = 0; i < value - 1; i++)TimeVector.push_back(lcg());
	for (int j = 0; j < 1000; j++)
	{

		auto start = high_resolution_clock::now();
		TimeVector.push_back(lcg());
		TimeVector.erase(std::remove(TimeVector.begin(), TimeVector.end(), lcg()), TimeVector.end());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		sum += (double)duration.count();
	}



	//сумму вектора времени делим на 1000 и возвращаем
	return sum / 1000;
}

int Check()
{
	int number = 0;
	while (!(cin >> number) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Enter a number" << endl;
	}
	return number;
}

void remove(std::vector<int>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}
void VectorReturn()
{
	int tmp;
	int flag = 1;
	std::vector<int> myVector;
	do {
		cout << "Введите эелмент вектора : ";
		tmp = Check();
		myVector.push_back(tmp);
		cout << "Добавить ещё? \n1)Да\n2)Нет\n";
		flag = Check();
		while (flag != 1 && flag != 2) {
			cout << "\nНет такого варианта ответа\n";
			_getch();
			system("CLS");
			cout << "Добавить ещё? \n1)Да\n2)Нет\n";
			flag = Check();
		}
	} while (flag == 1);
	system("CLS");
	cout << "Наш вектор: ";
	for (int i = 0; i < myVector.size(); i++) cout << myVector[i] << " ";
	Three B(myVector[0]);
	for (int i = 1; i < myVector.size(); i++) B.insert(myVector[i]);
	std::vector<int>newVector;
	for (int i = 0; i < myVector.size(); i++) {

		if (B.contains(myVector[i]))
		{
			B.erase(myVector[i]);

		}
		else newVector.push_back(myVector[i]);
	}
	remove(newVector); //удалим дубликаты
	cout << "\nПоворяющиеся элементы: ";
	for (int i = 0; i < newVector.size(); i++) cout << newVector[i] << " ";
}

int main() {

	setlocale(LC_ALL, "Russian");
	int tmp_value;
	cout << "Введите значение первого элемена дерева: ";
	tmp_value = Check();
	Three A(tmp_value);

	do {
		system("CLS");
		cout << "Наши элементы :\n";
		A.print();
		cout << "\nВыберите Действие : \n1)Добавить элемент в дерево\n2)Удалить элемент из дерева\n3)Проверить существует ли элемент\n4)Минимальное значение дерева\n5)Произвести тесты\n6)Заполнить вектор элементами и вернуть повторяющиея значения\n7)Выход\n";
		tmp_value = Check();
		switch (tmp_value)
		{
		case 1:
			cout << "Введите элемент:";
			tmp_value = Check();
			if (A.insert(tmp_value)) cout << "\nУспешно";
			tmp_value = 0;
			_getch();
			break;
		case 2:
			cout << "Введите значение удаляемого элемента:";
			tmp_value = Check();
			A.erase(tmp_value);
			tmp_value = 0;
			break;
		case 3:
			cout << "Введите элемент:";
			tmp_value = Check();
			if (A.contains(tmp_value)) cout << "\nСуществует";
			else cout << "\nНе существует";
			tmp_value = 0;
			_getch();
			break;
		case 4:
			if (A.FindM())cout << "Минимальное значение дерева : " << A.FindM();
			_getch();
			break;
		case 5:
			cout << "\nСреднее время заполнения контейнера на 1000: " << TestFirst(1000);
			cout << "\nСреднее время заполнения контейнера на 10 000:" << TestFirst(10000);
			cout << "\nСреднее время заполнения контейнера на 100 000: " << TestFirst(100000);
			cout << "\nСреднее время поиска в заполненном контейнере на 1000: " << TestSecond(1000);
			cout << "\nСреднее время поиска в заполненном контейнере на 10 000: " << TestSecond(10000);
			cout << "\nСреднее время поиска в заполненном контейнере на 100 000: " << TestSecond(100000);
			cout << "\nСреднее время заполнения и удаления элементов контейнера 1000: " << TestThird(1000);

			cout << "\nСреднее время заполнения и удаления элементов контейнера 10 000: " << TestThird(10000);
			cout << "\nСреднее время заполнения и удаления элементов контейнера 100 000: " << TestThird(100000);

			cout << "\nСреднее время заполнения вектора на 1000: " << TestVectorFirst(1000);
			cout << "\nСреднее время заполнения вектора на 10 000: " << TestVectorFirst(10000);
			cout << "\nСреднее время заполнения вектора на 100 000: " << TestVectorFirst(1000000);
			cout << "\nСреднее время поиска в заполненном векторе на 1000: " << TestVectorSecond(1000);
			cout << "\nСреднее время поиска в заполненном векторе на 10 000: " << TestVectorSecond(10000);
			cout << "\nСреднее время поиска в заполненном векторе на 100 000: " << TestVectorSecond(100000);
			cout << "\nСреднее время заполнения и удаления элементов контейнера 1000: " << TestVectorThird(1000);
			cout << "\nСреднее время заполнения и удаления элементов контейнера 10 000: " << TestVectorThird(10000);
			cout << "\nСреднее время заполнения и удаления элементов контейнера 100 000: " << TestVectorThird(100000);
			_getch();
			break;
		case 6:
			VectorReturn();
			_getch();
			break;
		default:
			break;
		}

	} while (tmp_value != 7);

}