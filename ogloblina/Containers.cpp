// ConsoleApplication7.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include<iterator>
#include<ctime>
#include<cstring>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{vector <int> vec(10);
	for (int i=0; i<vec.size(); i++) vec[i] = rand()%10;
	cout<<"Vector: ";
	srand(time(NULL));
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout," "));
	cout<<endl;
	
	system("pause");
	return 0;
}

