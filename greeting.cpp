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
	cout << "Курсовая работа по теме:\n";
	for (int i = 0; i < 60; i++)
		cout << " ";
		cout<<"Программная реализация задачи о распределении инвестиций\n";
		for (int i = 0; i < 70; i++)
			cout << " ";
		cout << " между предприятиями средствами С++.\n";
		for (int i = 0; i < 10; i++)
			cout << '\n';
		for (int i = 0; i < 100; i++)
			cout << " ";
		
		cout << "Программу написал студент группы 12002005\n";
		for (int i = 0; i < 124; i++)
			cout << " ";
		cout << "Давыдов Александр";


		for (int i = 0; i < 4; i++)
			cout << '\n';
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "Меню:\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "1.Условие и решение задачи путём использования вводимых данных\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "2.Условие и решение задачи на примере\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "3.Условие и решение задачи путём ввода и случайного выбора данных\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "4.Просмотреть результаты, записанные в файл\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "5.Условие и решение задачи путём использования данных из файла\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "6.Выход из программы\n\n";
		for (int i = 0; i < 60; i++)
			cout << " ";
		cout << "Выберите 1, 2, 3, 4, 5 или 6:       ";
		char k; cin >> k;

		
	return(k);
}