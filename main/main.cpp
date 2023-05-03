#include <iostream>
# include <clocale>
#include <conio.h>
#include<vector>

using namespace std;
template<typename T>
class Three {
	struct Leaves {
		T value;
		Leaves* Left = nullptr;
		Leaves* Right = nullptr;
	};
	int tmp_max = 0;
	int count = 0;
	int height = 0;
	int tmp_height = 0;
	Leaves* root = new Leaves;
	Leaves* rec_erase(Leaves* elem, T key) {
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
				struct Leaves* tmp = find_min(elem->Right);
				elem->value = tmp->value;
				elem->Right = rec_erase(elem->Right, tmp->value);
			}
			this->count--;
			//	this->height--;
		}
		return elem;
	}

	void rec_get_height(Leaves* root, int level) {
		if (root)
		{


			rec_get_height(root->Left, level + 1);
			rec_get_height(root->Right, level + 1);

		}

		if (this->tmp_height < level)this->tmp_height = level;
	}
	void need_balance() {
		this->tmp_height = 0;
		rec_get_height(this->root->Left, 0);
		int left_height = this->tmp_height;
		this->tmp_height = 0;
		rec_get_height(this->root->Right, 0);
		int right_height = this->tmp_height;

		if (left_height - right_height > 1 && right_height != left_height)//����� ������ �������
		{
			Leaves* tmp = this->root->Left->Right; //����� C
			Leaves* head = this->root;

			this->root = this->root->Left; //����� B 
			head->Left = tmp;
			this->root->Right = head;//



		}
		if (right_height - left_height > 1 && right_height != left_height) {
			Leaves* tmp = this->root->Right->Left; //����� A
			Leaves* head = this->root;

			this->root = this->root->Right; //����� B 
			head->Right = tmp;
			this->root->Left = head;//

		}
	}




	bool rec_insert(Leaves* elem, T key) {

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
				//this->height++;
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
				//this->height++;
			}
		}
		return true;

	}
	Leaves* rec_contains(Leaves* elem, T key) {
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
	void rec_print(Leaves* root, int level)
	{
		if (root)
		{


			rec_print(root->Left, level + 1);
			for (int i = 0; i < level; i++) cout << "      ";
			cout << root->value << endl;
			rec_print(root->Right, level + 1);

		}
		if (this->height < level)this->height = level;
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
	Leaves* find_min(Leaves* elem) {
		if (elem->Left) {
			return find_min(elem->Left);
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
		clear(root); this->count = 0;// this->height = 0;
	}
	Three(T key) {
		//Leaves* root = new Leaves;
		root->value = key;
		this->count = 1;
		//this->height = 1;
	}
	void print() {
		need_balance();
		this->height = 1;
		rec_print(this->root, 0);
		cout << "����� ������ " << this->height;


	}

	Three& operator=(const Three& src)
	{
		if (this == (&src)) { return *this; }
		clear(root);
		copy(root, src.root);
		this->count = src.count;
		return *this;
	}
	bool insert(T key) {

		bool tmp = rec_insert(this->root, key);
		if (tmp) this->count++;
		return tmp;

	}//������� ��������
	bool contains(T key) {
		if (rec_contains(this->root, key)) return true;
		return false;
	} //�������� ������� ��������

	int find_m() {
		if (this->count == 0) {
			std::cout << "��� ���������";
			return 0;
		}
		else return (find_min(this->root))->value;
	}

	bool erase(T key) {
		this->root = rec_erase(this->root, key);
		return true;
	} //�������� ��������
};


size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
#include <chrono>
using namespace std::chrono;

template<typename T>
double test_first_help(int value, bool Is_Vector)
{
	if (!Is_Vector) {
		//������  �����
		auto start = high_resolution_clock::now();
		Three<T> B(lcg());
		for (int i = 0; i < value - 1; i++) B.insert(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		return (double)duration.count();
	}
	vector<T> TimeVector(value);
	//��� 100 ���
	auto start = high_resolution_clock::now();
	for (int i = 0; i < value - 1; i++)  TimeVector.push_back(lcg());
	auto stop = high_resolution_clock::now();
	chrono::duration<double> duration = stop - start;
	return(double)duration.count();
}
template<typename T>
double test_second_help(int value, bool Is_Vector) {
	if (!Is_Vector) {
		Three<T> B(lcg());
		for (int j = 0; j < value; j++) B.insert(lcg());
		auto start = high_resolution_clock::now();
		B.contains(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		return (double)duration.count();
	}
	vector<T> TimeVector(value);
	for (int i = 0; i < value; i++)TimeVector.push_back(lcg());
	auto start = high_resolution_clock::now();
	find(TimeVector.begin(), TimeVector.end(), lcg());    //erase(lcg());
	auto stop = high_resolution_clock::now();
	chrono::duration<double> duration = stop - start;
	return (double)duration.count();


}
template<typename T>
double test_third_help(int value, bool Is_Vector = true)
{
	if (!Is_Vector) {
		Three <T>B(lcg());
		for (int i = 0; i < value - 1; i++)B.insert(lcg());
		auto start = high_resolution_clock::now();
		B.insert(lcg());
		B.erase(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		return (double)duration.count();
	}


}
template<typename T>
double test_first(T value) {
	double sum = 0;

	//��� 100 ���
	for (int j = 0; j < 100; j++) {

		sum += test_first_help<T>(value, false);
	}
	//���������� �����
	//����� �������� � ������

	//����� ������� ������� ����� �� 100 � ����������
	return sum / 100;
}
template<typename T>
double test_second(T value) {
	double  sum = 0;
	//��� 1000 ���
	//������  �����
	for (int j = 0; j < 1000; j++) {
		sum += test_second_help<T>(value, false);
	}
	//���������� �����
	//����� �������� � ������

	//����� ������� ������� ����� �� 1000 � ����������

	return sum / 1000;
}
template<typename T>
double test_third(T value) {

	double  sum = 0;
	//��� 1000 ���
	//������  �����
	for (int j = 0; j < 1000; j++) {
		sum += test_third_help<T>(value);
	}
	//���������� �����
	//����� �������� � ������

	//����� ������� ������� ����� �� 1000 � ����������
	return sum / 1000;
}


template<typename T>
double test_vector_first(T value) {

	double sum = 0;
	//����� �������� � ������
	for (int j = 0; j < 100; j++) {

		sum += test_first_help<T>(value, true);
	}
	//����� ������� ������� ����� �� 100 � ����������
	return sum / 100;
}
template<typename T>
double test_vector_second(T value) {

	//��� 1000 ���
	//������  �����

	double sum = 0;
	for (int j = 0; j < 1000; j++) {

		sum += test_second_help<T>(value, true);

	}
	//���������� �����


	//����� ������� ������� ����� �� 1000 � ����������
	return sum / 1000;
}
template<typename T>
double test_vector_third(T value) {
	vector<T> TimeVector(value);
	//��� 1000 ���
	//������  �����
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



	//����� ������� ������� ����� �� 1000 � ����������
	return sum / 1000;
}

int CheckChoise()
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

double Check()
{
	double number = 0;
	while (!(cin >> number) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Input correct value" << endl;
	}
	return number;
}

template<typename T>
void remove(std::vector<T>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}
template<typename T>
void vector_return()
{
	T tmp;
	int flag = 1;
	std::vector<T> myVector;
	do {
		cout << "������� ������� ������� : ";
		tmp = Check();
		myVector.push_back(tmp);
		cout << "�������� ���? \n1)��\n2)���\n";
		flag = CheckChoise();
		while (flag != 1 && flag != 2) {
			cout << "\n��� ������ �������� ������\n";
			_getch();
			system("CLS");
			cout << "�������� ���? \n1)��\n2)���\n";
			flag = CheckChoise();
		}
	} while (flag == 1);
	system("CLS");
	cout << "��� ������: ";
	for (int i = 0; i < myVector.size(); i++) cout << myVector[i] << " ";
	Three <T>B(myVector[0]);
	for (int i = 1; i < myVector.size(); i++) B.insert(myVector[i]);
	std::vector<T>newVector;
	for (int i = 0; i < myVector.size(); i++) {

		if (B.contains(myVector[i]))
		{
			B.erase(myVector[i]);

		}
		else newVector.push_back(myVector[i]);
	}
	remove(newVector); //������ ���������
	cout << "\n������������ ��������: ";
	for (int i = 0; i < newVector.size(); i++) cout << newVector[i] << " ";
}

template<typename T>
void main1() {


	T tmp_value;
	cout << "������� �������� ������� ������� ������: ";
	tmp_value = Check();
	Three<T> A(tmp_value);
	int tmp;
	do {
		system("CLS");
		cout << "���� �������� :\n";
		A.print();
		cout << "\n�������� �������� : \n1)�������� ������� � ������\n2)������� ������� �� ������\n3)��������� ���������� �� �������\n4)����������� �������� ������\n5)���������� �����\n6)��������� ������ ���������� � ������� ������������ ��������\n7)�����\n";
		tmp = CheckChoise();
		switch (tmp)
		{
		case 1:
			cout << "������� �������:";
			tmp_value = Check();
			if (A.insert(tmp_value)) cout << "\n�������";
			tmp = 0;
			_getch();
			break;
		case 2:
			cout << "������� �������� ���������� ��������:";
			tmp_value = Check();
			A.erase(tmp_value);
			tmp = 0;
			break;
		case 3:
			cout << "������� �������:";
			tmp_value = Check();
			if (A.contains(tmp_value)) cout << "\n����������";
			else cout << "\n�� ����������";
			tmp = 0;
			_getch();
			break;
		case 4:
			if (A.find_m())cout << "����������� �������� ������ : " << A.find_m();
			_getch();
			break;
		case 5:
			cout << "\n������� ����� ���������� ���������� �� 1000: " << test_first(1000);
			cout << "\n������� ����� ���������� ���������� �� 10 000:" << test_first(10000);
			cout << "\n������� ����� ���������� ���������� �� 100 000: " << test_first(100000);
			cout << "\n������� ����� ������ � ����������� ���������� �� 1000: " << test_second(1000);
			cout << "\n������� ����� ������ � ����������� ���������� �� 10 000: " << test_second(10000);
			cout << "\n������� ����� ������ � ����������� ���������� �� 100 000: " << test_second(100000);
			cout << "\n������� ����� ���������� � �������� ��������� ���������� 1000: " << test_third(1000);

			cout << "\n������� ����� ���������� � �������� ��������� ���������� 10 000: " << test_third(10000);
			cout << "\n������� ����� ���������� � �������� ��������� ���������� 100 000: " << test_third(100000);

			cout << "\n������� ����� ���������� ������� �� 1000: " << test_vector_first(1000);
			cout << "\n������� ����� ���������� ������� �� 10 000: " << test_vector_first(10000);
			cout << "\n������� ����� ���������� ������� �� 100 000: " << test_vector_first(1000000);
			cout << "\n������� ����� ������ � ����������� ������� �� 1000: " << test_vector_second(1000);
			cout << "\n������� ����� ������ � ����������� ������� �� 10 000: " << test_vector_second(10000);
			cout << "\n������� ����� ������ � ����������� ������� �� 100 000: " << test_vector_second(100000);
			cout << "\n������� ����� ���������� � �������� ��������� ���������� 1000: " << test_vector_third(1000);
			cout << "\n������� ����� ���������� � �������� ��������� ���������� 10 000: " << test_vector_third(10000);
			cout << "\n������� ����� ���������� � �������� ��������� ���������� 100 000: " << test_vector_third(100000);
			_getch();
			break;
		case 6:
			vector_return<T>();
			_getch();
			break;
		default:
			break;
		}

	} while (tmp != 7);

}

int main() {
	setlocale(LC_ALL, "Russian");
	int tmp;
	cout << "�������� �������� ������:\n1)int\n2)double\n3)float\n";
	tmp = CheckChoise();
	switch (tmp)
	{
	case 1:
		main1<int>();
		break;
	case 2:
		main1<double>();
		break;
	case 3:
		main1<float>();
		break;
	default:
		cout << "\n��� ������ ��������\n";
		_getch();
		system("CLS");

		break;
	}

}