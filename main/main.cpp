#include <iostream>
# include <clocale>
#include <conio.h>
#include<vector>
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
	} //проверка наличия элемента

	int FindM() {

		return (FindMin(this->root))->value;
	}
	void erase(int key) {
		this->root = rec_erase(this->root, key);

	} //удаление элемента
};


size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

float TestFirst(int value) {

	//для 100 раз
	//Отсечь  время
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 100 и возвращаем
	return 1;
}
float TestSecond(int value) {

	//для 1000 раз
	//Отсечь  время
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.contains(lcg());
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}

float TestThird(int value) {

	//для 1000 раз
	//Отсечь  время
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	for (int i = 0; i < value - 1; i++)
	{
		B.erase(lcg());
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}
float TestVectorFirst(int value) {

	vector<double> TimeVector(value);
	//для 100 раз
	clock_t t0 = clock();
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	clock_t t1 = clock();//остановить время
	//время добавить в вектор
	cout << (double)(t1 - t0) / CLOCKS_PER_SEC;
	TimeVector.push_back((double)(t1 - t0) / CLOCKS_PER_SEC);
	//сумму вектора времени делим на 100 и возвращаем
	return 1;
}
float TestVectorSecond(int value) {

	//для 1000 раз
	//Отсечь  время
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.contains(lcg());
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}

float TestVectorThird(int value) {

	//для 1000 раз
	//Отсечь  время
	Three B(lcg());
	for (int i = 0; i < value - 1; i++)
	{
		B.insert(lcg());
	}
	for (int i = 0; i < value - 1; i++)
	{
		B.erase(lcg());
	}
	//остановить время
	//время добавить в вектор

	//сумму вектора времени делим на 1000 и возвращаем
	return 1;
}

void RecElem() {
	/*
	Создаем вектор2
	Для каждого элемента elem1 вектора 1:
		если элемент есть в векторе2: отмена
		иначе:
			count=0
			Для каждого элемента elem2 вектора1:
				если elem1==elem2:
					count++;
			если count>1:  elem1 добавим в вектор2

	cout<<"Повторяющиеся элементы: "<< вектор2
}


int main() {
	/*Three A(20);
	A.insert(-110);
	A.insert(25);
	A.insert(5);
	A.insert(10);
	A.insert(30);
	A.insert(22);

	A.print();
	cout<<A.contains(100);
	cout << A.Find();
	A.erase(25);
	cout << endl;
	A.print();
	*/
	setlocale(LC_ALL, "Russian");
	int tmp_value;
	cout << "Введите значение первого элемена дерева: ";
	cin >> tmp_value;
	Three A(tmp_value);

	do {
		system("CLS");
		cout << "Наши элементы :\n";
		A.print();
		cout << "\nВыберите Действие : \n1)Добавить элемент в дерево\n2)Удалить элемент из дерева\n3)Проверить существует ли элемент\n4)Минимальное значение дерева\n\n__ТЕСТЫ_ДЛЯ_ДЕРЕВА__\n\n5)Тест на заполнение\n6)Тест на поиск\n7)Тест на добавлеие удаление \n\n__ТЕСТЫ_ДЛЯ_ВЕКТОРОВ__\n\n8)Тест на заполнение\n9)Тест на поиск\n10)Тест на добавлеие удаление \n11)Заполнить вектор элементами и вернуть повторяющиея значения\n12)Выход";
		cin >> tmp_value;
		switch (tmp_value)
		{
		case 1:
			cout << "Введите элемент:";
			cin >> tmp_value;
			if (A.insert(tmp_value)) cout << "\nУспешно";
			else cout << "\nНе получилось";
			_getch();
			break;
		case 2:
			cout << "Введите значение удаляемого элемента:";
			cin >> tmp_value;
			A.erase(tmp_value);
			break;
		case 3:
			cout << "Введите элемент:";
			cin >> tmp_value;
			if (A.contains(tmp_value)) cout << "\nСуществует";
			else cout << "\nНе существует";
			_getch();
		case 4:
			cout << "Минимальное значение дерева : " << A.FindM();
			_getch();
		case 5:
			do {
				cout << "Выберите сколько значений протестируем:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)Отмена";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//сохраняем в вектор ячейка 1
					cout << "Среднее время выполения теста: " << TestFirst(1000);
					_getch();
					break;
				case 2:
					//сохраняем в вектор ячейка 2
					cout << "Среднее время выполения теста: " << TestFirst(10000);
					_getch();
					break;
				case 3:
					//сохраняем в вектор ячейка 3
					cout << "Среднее время выполения теста: " << TestFirst(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\nНет такого элемента\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			break;
		case 6:
			do {
				cout << "Выберите сколько значений протестируем:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)Отмена";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//сохраняем в вектор ячейка 4
					cout << "Среднее время выполения теста: " << TestSecond(1000);
					_getch();
					break;
				case 2:
					//сохраняем в вектор ячейка 5
					cout << "Среднее время выполения теста: " << TestSecond(10000);
					_getch();
					break;
				case 3:
					//сохраняем в вектор ячейка 6
					cout << "Среднее время выполения теста: " << TestSecond(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\nНет такого элемента\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			break;
		case 7:
			do {
				cout << "Выберите сколько значений протестируем:\n1) 1000 \n2) 10 000\n 3) 100 000  \n4)Отмена";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//сохраняем в вектор ячейка 7
					cout << "Среднее время выполения теста: " << TestThird(1000);
					_getch();
					break;
				case 2:
					//сохраняем в вектор ячейка 8
					cout << "Среднее время выполения теста: " << TestThird(10000);
					_getch();
					break;
				case 3:
					//сохраняем в вектор ячейка 9
					cout << "Среднее время выполения теста: " << TestThird(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\nНет такого элемента\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			break;
		case 8:
			do {
				cout << "Выберите сколько значений протестируем:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)Отмена";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//сохраняем в вектор ячейка 1
					cout << "Среднее время выполения теста: " << TestVectorFirst(1000);
					_getch();
					break;
				case 2:
					//сохраняем в вектор ячейка 2
					cout << "Среднее время выполения теста: " << TestVectorFirst(10000);
					_getch();
					break;
				case 3:
					//сохраняем в вектор ячейка 3
					cout << "Среднее время выполения теста: " << TestVectorFirst(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\nНет такого элемента\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			break;
		case 9:
			do {
				cout << "Выберите сколько значений протестируем:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)Отмена";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//сохраняем в вектор ячейка 4
					cout << "Среднее время выполения теста: " << TestVectorSecond(1000);
					_getch();
					break;
				case 2:
					//сохраняем в вектор ячейка 5
					cout << "Среднее время выполения теста: " << TestVectorSecond(10000);
					_getch();
					break;
				case 3:
					//сохраняем в вектор ячейка 6
					cout << "Среднее время выполения теста: " << TestVectorSecond(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\nНет такого элемента\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			break;
		case 10:
			do {
				cout << "Выберите сколько значений протестируем:\n1) 1000 \n2) 10 000\n 3) 100 000  \n4)Отмена";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//сохраняем в вектор ячейка 7
					cout << "Среднее время выполения теста: " << TestVectorThird(1000);
					_getch();
					break;
				case 2:
					//сохраняем в вектор ячейка 8
					cout << "Среднее время выполения теста: " << TestVectorThird(10000);
					_getch();
					break;
				case 3:
					//сохраняем в вектор ячейка 9
					cout << "Среднее время выполения теста: " << TestVectorThird(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\nНет такого элемента\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			break;
		case 11:
			//создаем вектор 
			int tmp_value1;
			do {
				cout << "Наш вектор: \n";
				//выводм вектор 
				cout << "\nДобавить ещё?\n1)Да\n2)Нет ";
				cin >> tmp_value1;
				switch (tmp_value1)
				{
				case 1:
					cout << "Введите элемент, который добавим в вектор: ";
					cin >> tmp_value;
					//добавляем в вектор значения
				case 2:
					break;
				default:
					cout << "\nНет такого элемента\n";
					_getch();
					break;
				}

			} while (tmp_value1 != 2);

			cout << "Наш вектор:";
			RecElem();

		default:
			break;
		}

	} while (tmp_value != 12);

}