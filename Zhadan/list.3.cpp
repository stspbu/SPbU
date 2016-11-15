#include "stdafx.h"
#include <iostream>

using namespace std;

struct list
{
	int inf;
	list *next;
	list *last;
};

list* in(list* first,int n)
{
	
	list *p = first;

	cout << "������� 1 ������� ������ ";
	cin >> p->inf;

	for (int i = 0; i<n - 1; i++)
	{
		p->next = new list;
		p->next->last = p;
		p = p->next;
		cout << "������� " << i + 2 << " ������� ������ ";
		cin >> p->inf;
	}
	p->next = 0;

	return p;
}


void  out(list *a)
{
	while (a)
	{
		cout << a->inf << " ";
		a = a->next;
	};
	cout << endl;
}

void sum(list* first,list* p)
{
	int sum = 0;
	while (first)
	{
		sum = sum + first->inf*p->inf;
		first = first->next;
		p = p->last;
	}
	cout << "3) �1*�n + �2*�n-1 + ... + �n*�1 = " << sum << endl;

}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	char v = '0';
	cout << "������� ���������� ��������� ������ ";
	cin >> n;
	list *first = new list;
	first->last = 0;
	list *p = in(first,n);
	system("cls"); 

	while (v != '4')
	{
		cout << "1) ������ ����� ������ " << endl;
		cout << "2) ������� ������ " << endl;
		cout << "3) ���������:  �1*�n + �2*�n-1 + ... + �n*�1" << endl;
		cout << "4) ����� " << endl;
		cin >> v;
		switch (v)
		{
		case '1':
			system("cls");
			cout << "������� ���������� ��������� ������ ";
			cin >> n;
			p = in(first, n);
			system("cls");
			break;
		case '2':
			system("cls");
			out(first);
			break;
		case '3':
			system("cls");
			sum(first, p);
			break;
		}

	}


	return 0;
}
