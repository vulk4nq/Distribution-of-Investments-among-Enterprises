#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;
char mainScreen()
{
	
	for (int i = 0;i< 6; i++)
		cout << '\n';
	for (int i = 0; i <75; i++)
		cout << " ";
	cout << "�������� ������ �� ����:\n";
	for (int i = 0; i < 60; i++)
		cout << " ";
		cout<<"����������� ���������� ������ � ������������� ����������\n";
		for (int i = 0; i < 70; i++)
			cout << " ";
		cout << " ����� ������������� ���������� �++.\n";
		for (int i = 0; i < 10; i++)
			cout << '\n';
		for (int i = 0; i < 100; i++)
			cout << " ";
		
		cout << "��������� ������� ������� ������ 12002005\n";
		for (int i = 0; i < 124; i++)
			cout << " ";
		cout << "������� ���������";


		for (int i = 0; i < 4; i++)
			cout << '\n';
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "����:\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "1.������� � ������� ������ ���� ������������� �������� ������\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "2.������� � ������� ������ �� �������\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "3.������� � ������� ������ ���� ����� � ���������� ������ ������\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "4.����������� ����������, ���������� � ����\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "5.������� � ������� ������ ���� ������������� ������ �� �����\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "6.����� �� ���������\n\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "�������� 1, 2, 3, 4, 5 ��� 6:       ";
		char k; cin >> k;

		
	return(k);
}