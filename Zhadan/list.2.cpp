#include "stdafx.h"
#include <iostream>

using namespace std;

struct list
{
	int inf;
	list *next;
	list *last;
};

list* in(int n)
{
	list *first = new list;	
	first->last = 0; 
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

	return first;
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

list* add(list *a, int c)
{
	int k, n;
	list* w = new list;
	cout << "������� ����� ������� ";
	cin >> k;
	cout << "������� ����� �� 1 - " << c+1 << endl;

	cin >> n;

	if (n == 1)
	{
		w->next = a;
		w->last = 0;
		w->inf = k;
		a->last = w;
		a = w;
	}
	else
	{
		w = a;
		list *v = new list;
		for (int i = 0; i < n - 2; i++)	w = w->next;
		v->next = w->next;
		v->inf = k;
		w->next = v;
		v->last = w;
	}
	return a;
}

list* del(list *a, int c)
{
	int n;
	list* w = new list;
	cout << "������� ����� �� 1 - " << c << endl;
	cin >> n;

	if (n == 1)
	{
		w = a->next;
		w->last = 0;
		delete a;
	}
	else
	{
		w = a;
		list* p = new list;
		list* z = new list;
		z = a;
		for (int i = 0; i < n - 2; i++) z = z->next;
		p = z->next;
		z->next = p->next;
		if(n!=c) z->next->last = z;
		delete p;
	}
	return w;
}

bool find(list* a)
{
	int k;
	bool c = 0;
	cout << "������� ������� ";
	cin >> k;
	int i = 0;
	while ((a!=0) & (c==0) )
	{
		if (a->inf == k) c = 1;
		a = a->next;
		i++;
	}
	if (c) cout << "������� �����������" << endl << "��� ����� " << i << endl;
	else cout << "������� ����������" << endl;
	return c;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	char v = '0';
	cout << "������� ���������� ��������� ������ ";
	cin >> n;
	list *first = in(n);
	system("cls");

	while (v != '6')
	{
		cout << "1) ������ ����� ������ " << endl;
		cout << "2) ������� ������ " << endl;
		cout << "3) �������� ����� ������� " << endl;
		cout << "4) ������� ������� " << endl;
		cout << "5) ����� ��������� �������" << endl;
		cout << "6) ����� " << endl;
		cin >> v;
		switch (v)
		{
		case '1':
			system("cls");
			cout << "������� ���������� ��������� ������ ";
			cin >> n;
			first = in(n);
			system("cls");
			break;
		case '2':
			system("cls");
			out(first);
			break;
		case '3':
			system("cls");
			first = add(first, n);
			n = n + 1;
			break;
		case '4':
			system("cls");
			first = del(first, n);
			n = n - 1;
			break;
		case '5':
			system("cls");
			find(first);
			break;
		}

	}


	return 0;
}
