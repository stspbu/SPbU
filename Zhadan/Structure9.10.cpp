#include "stdafx.h"
#include "iostream"
#include <fstream>
#include <string>
#include <algorithm>   
using namespace std;
const int q = 4;

struct Pharmacy
{
	int number;
	string name;
	int k;
	int price;
	int d, m, y;
	int srok;
};


void out(Pharmacy &A)
{
	cout << "����� ������: " << A.number << endl;
	cout << "�������� ���������: " << A.name << endl;
	cout << "����������: " << A.k << endl;	
	cout << "���� �� ��������: " << A.price << endl;
	cout << "���� �����������: " << A.d << " " << A.m << " " << A.y << endl;
	cout << "���� ��������: " << A.srok << endl << endl;
}

bool Number(Pharmacy &A, Pharmacy &B)
{
	return A.number < B.number;
};


bool Name(Pharmacy &A, Pharmacy &B)
{
	bool n = 0;
	if (A.name.compare(B.name) < 0) n = 1;
	else n = 0;
	return n;
}; 


bool Data(Pharmacy &A, Pharmacy &B)
{
	return (A.y < B.y) | ((A.y == B.y)&(A.m < B.m)) | ((A.y == B.y)&(A.m == B.m)&(A.d < B.d));
};

int main()
{
	string a;
	char v='0';
	setlocale(LC_ALL, "Russian");
	Pharmacy mas[q];
	
	ifstream in("input.txt");
	
	
	for (int i = 0; i < q; i++)
	{
		in >> mas[i].number;
		getline(in, a);
		getline(in, mas[i].name);
		in >> mas[i].k;
		getline(in, a);
		in >> mas[i].price;
		getline(in, a);
		in >> mas[i].d;
		in >> mas[i].m;
		in >> mas[i].y;
		getline(in, a);
		in >> mas[i].srok;
		getline(in, a);
	};
	in.close();

	
	for (int i = 0; i < q; i++)
	{
		out(mas[i]);
	};

	while (v != '4')
	{
		cout << "�������� ��� ����������: \n";
		cout << "1) �� ������ ������ \n";
		cout << "2) �� ������������ ��������� \n";
		cout << "3) �� ���� ����������� \n";
		cout << "4) ����� \n";
		cin >> v;
		system("cls");

		switch (v)
		{
		case '1':
			sort(mas, mas + q, Number);

			for (int i = 0; i < q; i++)
			{
				out(mas[i]);
			};
			break;
		case '2':
			sort(mas, mas + q, Name);

			for (int i = 0; i < q; i++)
			{
				out(mas[i]);
			};
			break;
		case '3':
			sort(mas, mas + q, Data);

			for (int i = 0; i < q; i++)
			{
				out(mas[i]);
			};

			break;
		}

		system("pause");
		system("cls");
	}

	return 0;
}