#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

int prd, srdstv; unsigned short kolvo = 0;//prd-предприятия srdstv-инвестируемые средства kolvo-кол-во решений
struct Rezultat {
	unsigned short* posl = new unsigned short[prd];//последовательность кол-ва инвестируемых средств в предприятия
	unsigned short sum;//конечная сумма решения
}; Rezultat* Arr = new Rezultat[1000];//Массив решений
char mainScreen();
bool ReshenieVvod();
bool ReshenieRandom();
bool ResheniePrimer();
bool ChtenieIsFile();
void req();
void sortOfMassiveIndex();


int main()
{
	system("color F0");
	//system("cls");
	setlocale(LC_ALL, "Russian");
	
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
	bool flag = 1;
	while (flag)
	{
		switch (mainScreen())
		{
		case '1':system("cls"); if (ReshenieVvod())return 0; system("cls"); break;
		case '2':system("cls"); if (ResheniePrimer())return 0; system("cls"); break; 
		case '3': system("cls"); if (ReshenieRandom())return 0; system("cls"); break;
		case '4': system("cls"); if (ChtenieIsFile())return 0; system("cls"); break;
		case '5':system("cls"); return 0; 
		default:cout<<"\n Ввод неверный, повторите попытку!";


		}
	}

	

}




void req(unsigned short* massiveindex, unsigned short*** promezhRezult, int k, int x, Rezultat* prez) {

	if (srdstv > 10 || prd > 10||srdstv==prd) {
		if (k < prd - 1) {
				if (srdstv - x - 1 == promezhRezult[k][srdstv - x - 1][0])
				{
					prez[kolvo].posl[k] = promezhRezult[k][srdstv - x - 1][0];
					for (int f = k; f < prd + 1; f++) prez[kolvo].posl[f + 1] = 0;
					kolvo++;
				}
				else {
					prez[kolvo].posl[k] = promezhRezult[k][srdstv - x - 1][0];
					req(massiveindex, promezhRezult, k + 1, promezhRezult[k][srdstv - x - 1][0] + x, prez);
					if (k > 0 && kolvo > 0) prez[kolvo].posl[0] = prez[kolvo - 1].posl[0];
				}
		}
		else {prez[kolvo].posl[k] = promezhRezult[k][srdstv - x - 1][0];
			kolvo++;
		}
	}
	else if (k < prd - 1) {
		for (int i = 0; i < massiveindex[(k) * (srdstv)+x]; i++)
		{
			if (srdstv - x - 1 == promezhRezult[k][srdstv - x - 1][i])
			{
				prez[kolvo].posl[k] = promezhRezult[k][srdstv - x - 1][i];
				for (int f = k; f < prd + 1; f++) prez[kolvo].posl[f+1] = 0;
				kolvo++;
			}
			else {
				prez[kolvo].posl[k] = promezhRezult[k][srdstv - x - 1][i];
				req(massiveindex, promezhRezult, k + 1, promezhRezult[k][srdstv - x - 1][i] + x, prez);
				if (k > 0 && kolvo > 0) prez[kolvo].posl[0] = prez[kolvo - 1].posl[0];
			}
		}
	}
	else {prez[kolvo].posl[k] = promezhRezult[k][srdstv - x - 1][0];
		kolvo++;
	}




}
void sortOfMassiveIndex(unsigned short* massiveindex)
{

	if (srdstv * prd % 2 == 0) {
		massiveindex[srdstv * prd / 2 - 1] = massiveindex[srdstv * prd / 2 - 1] + massiveindex[srdstv * prd / 2];
		massiveindex[srdstv * prd / 2] = massiveindex[srdstv * prd / 2 - 1] - massiveindex[srdstv * prd / 2];
		massiveindex[srdstv * prd / 2 - 1] = massiveindex[srdstv * prd / 2 - 1] - massiveindex[srdstv * prd / 2];
		for (int i = 0, j = srdstv * prd - 1; i < srdstv * prd / 2 - 1; i++, j--)
		{


			massiveindex[i] = massiveindex[i] + massiveindex[j];
			massiveindex[j] = massiveindex[i] - massiveindex[j];
			massiveindex[i] = massiveindex	[i] - massiveindex[j];

		}
	}
	else {
		for (int i = 0, j = srdstv * prd - 1; i < srdstv * prd / 2; i++, j--)
		{

			massiveindex[i] = massiveindex[i] + massiveindex[j];
			massiveindex[j] = massiveindex[i] - massiveindex[j];
			massiveindex[i] = massiveindex[i] - massiveindex[j];

		}
	}

}
bool ChtenieIsFile() 
{
	ifstream file("Rezultati.txt");
	if (!file)
	{
		cout << "Файл не открыт\n\n";
		return 0;
	}
	else
	{
		string stroka;
		cout << "\n\n\n\n   В файле с результатами записана следующая информация: \n\n";
		do {
			
			getline(file, stroka);
			cout <<"        " <<stroka<<endl<<endl;
			
		} while (!file.eof());
	}
	cout << endl;
	cout << endl;
	int flag;
	cout << "Для выхода из программы введите 0, чтобы выйти в меню введите 1:   ";
	kolvo = 0;
	flag = 2;
	while (flag != 0 && flag != 1) {
		cin >> flag;
		if (flag == 0 || flag == 1)
			return(!flag);
	}
}
bool ReshenieVvod()
{
	bool check = 1;
	cout << "  \n\n\n       Задача:\n\n\n     Совет директоров фирмы рассматривает предложения относительно прироста производственных мощностей для увеличения выпуска однородной продукции\n     на n предприятиях принадлежащих фирме.Для модернизации предприятий предложено инвестировать средства в объеме X усл.ден.ед. с дискретностью \n     1 усл.ден.ед. Прирост выпуска продукции зависит от выделенной суммы ,а его значения даны предприятиями и содержатся в таблице. Найти\n     распределение инвестиций между предприятиями,обеспечивающее фирме максимальный прирост продукции, при чем на одно предприятие можно\n     осуществить только одну инвестицию.\n\n\n";
	char f;
	while (check) {
		cout << "\n     Хотите ввести данные из\"IshodnieDanie.txt\"?(1-Да/0-Нет):  ";
		cin >> f;
		if (f == '0' || f == '1')check = 0;

	}
	
	check = 1;
	if (f == '1') {
		ifstream file("IshodnieDanie.txt");
		string line; int count_row = 0, count_column = 0;
		do {
			
			
			getline(file, line); 
			count_row++;
			

		} while (!file.eof());
		file.close();
		file.open("IshodnieDanie.txt");
		getline(file, line);
		for (int i = 1; i < line.length(); i++)
		{
			if (line[i] == 32) {
				if (count_column == 0) { count_column += 2; }
				else count_column++;

			}
		}
		prd = count_row-1 ;
		srdstv = count_column+1;
		file.close();

	}
	if (f == '0') {
		while (check)
		{
			cout << "\n     Введите N(>=3) кол-во предприятий:  "; cin >> prd;
			if (prd >= 3 && prd <= 600) check = 0;
			else cout << "Введите число больше 2 и меньше 600: ";
		}

		while (!check) {
			cout << "\n     Введите X объём инвестируемых средств:  "; cin >> srdstv; cout << "\n";
			srdstv++;
			if (srdstv <= 600 && srdstv >= 0) check = 1;
			else cout << "Введите неотрицательное число  меньше 600: ";
		}

		cout << "\n     Поочерёдно введите приросты выпуска продукции предприятий:\n";
	}
	unsigned short** matr = new unsigned short* [prd];//матрица с введеными данными где строки средства, а предприятия столбцы
	for (int i = 0; i < prd; i++) matr[i] = new unsigned short[srdstv];

	unsigned short*** arraymatr = new unsigned short** [prd];//матрицы для решений
	for (int i = 0; i < prd; i++)
	{
		arraymatr[i] = new unsigned short* [srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			arraymatr[i][j] = new unsigned short[srdstv];
			for (int k = 0; k < srdstv; k++)
				arraymatr[i][j][k] = 0;
		}
	}

	unsigned short*** prRez = new unsigned short** [prd];//промежуточный результат
	for (int i = 0; i < prd; i++)
	{
		prRez[i] = new unsigned short* [srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			prRez[i][j] = new unsigned short[srdstv];
			for (int k = 0; k < srdstv; k++)
				prRez[i][j][k] = 0;
		}
	}
	unsigned short** promezhMax = new unsigned short* [prd];//промежуточный результат
	for (int i = 0; i < prd; i++)
	{
		promezhMax[i] = new unsigned short[srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			promezhMax[i][j] = 0;
		}
	}
	

	int max = 0;
	unsigned short* massindex = new unsigned short[prd * srdstv];
	int count2 = 0;

	if (f == '1') {
		ifstream file("IshodnieDanie.txt");
		string line;
		do {
			for (int i = 0; i < prd; i++)
			{
				matr[i][0] = 0;
				for (int j = 1; j < srdstv; j++)
				{
					
					file >> matr[i][j];
				}
			}

		} while (!file.eof());
		file.close();
	}

	if (f == '0') {
		for (int i = 0; i < prd; i++)
		{
			matr[i][0] = 0;
			for (int j = 1; j < srdstv; j++)
			{
				cout << "\n     g" << i + 1 << "(x = " << j << ") = ";
				int input;
				cin >> input;
				if (input < 0||input>60000) {
					cout << "\nВы ввели отрицательное число или число больше допустимого, это не допустимо программой. Введите ещё раз\n";
					j--;
				}
				else matr[i][j] = input;
			}
		}
	}
	system("cls");
	cout << "  \n\n\n       Задача:\n\n\n     Совет директоров фирмы рассматривает предложения относительно прироста производственных мощностей для увеличения выпуска однородной продукции\n     на n предприятиях принадлежащих фирме.Для модернизации предприятий предложено инвестировать средства в объеме X усл.ден.ед. с дискретностью \n     1 усл.ден.ед. Прирост выпуска продукции зависит от выделенной суммы ,а его значения даны предприятиями и содержатся в таблице. Найти\n     распределение инвестиций между предприятиями,обеспечивающее фирме максимальный прирост продукции, при чем на одно предприятие можно\n     осуществить только одну инвестицию.\n\n\n";
	if (prd < 11 && prd >= 3) {
		cout << "     Исходная матрица: \n\n\n     ";

		for (int i = 0; i < 16; i++)
			cout << "*";
		if (prd / 2 != 0)
		{
			for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		}
		else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";

		cout << "\n     | Инвестиции, |";


		cout << setiosflags(ios::left) << setw(13 * prd - 1) << "Прирост выпуска продукции, усл.ден.ед." << setiosflags(ios::right);

		cout << setw(1) << "|" << '\n';

		cout << "     |             |";

		for (int i = 0; i < 13 * prd - 1; i++) cout << "*";


		cout << "|\n";


		cout << "     | усл.ден.ед. |";
		for (int i = 0; i < prd; i++)cout << " g" << setiosflags(ios::left) << setw(6) << i + 1 << "(x) |";//11
		cout << endl << "     ";

		for (int i = 0; i < 16; i++)
			cout << "*";
		if (prd / 2 != 0)
		{
			for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		}
		else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";
		cout << endl;
		for (int i = 0; i < srdstv; i++)
		{
			cout << "     |  " << setw(9) << i;
			cout << "  |";
			for (int j = 0; j < prd; j++)
			{
				cout << "  " << setw(8) << matr[j][i];
				cout << "  |";

			}
			cout << endl << "     ";
			for (int i = 0; i < 16; i++)
				cout << "*";
			if (prd / 2 != 0)
			{
				for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
			}
			else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";

			cout << endl;

		}
	}
	else if (prd > 11) cout << "     Исходную матрицу невозможно вывести, она не влезает на ширину экрана";


	cout << endl;
	if (srdstv < 13) {
		cout << "     Вывести матрицы решений?:";
		cout << endl << "     1. Да        0.Нет    :";
		cin >> check;
	}
	else check = 0;

	cout << "\n\n\n";
	for (int k = prd - 1; k > -1; k--)
	{
		if (check) {
			cout << "     Шаг №" << k + 1;

			cout << "      Средства|";
			for (int j = 0; j < srdstv; j++) {
				cout << "x" << setiosflags(ios::left) << setw(6) << j << setiosflags(ios::right) << "|";
			}
			cout << "\n                 --------";


			for (int j = 0; j < srdstv * 8; j++)
			{
				cout << "-";
			}
		}
		cout << endl;
		for (int i = 0; i < srdstv; i++)
		{


			if (check)cout << "                     " << setw(3) << i << " |";

			int count = 0;
			for (int j = 0; j < srdstv; j++)
			{

				if (k != prd - 1)
				{
					if (i == j)
					{
						arraymatr[k][i][j] = matr[k][i];
						if (arraymatr[k][i][j] > max) { max = arraymatr[k][i][j]; }
					}
					else {
						if (j <= i)
						{
							if (j < i) {
								arraymatr[k][i][j] = matr[k][j] + promezhMax[k + 1][i - count];
								count++;
							}
							if (arraymatr[k][i][j] > max) { max = arraymatr[k][i][j]; }


						}
					}
					promezhMax[k][i] = max;

				}
				else { arraymatr[k][i][i] = matr[k][i]; promezhMax[k][i] = matr[k][i]; prRez[k][i][0] = i; }
				if (check)cout << setw(7) << arraymatr[k][i][j] << "|";


			}if (check) {
			cout << endl;
			cout << "                 --------";
			for (int j = 0; j < srdstv * 8; j++)
			{
				cout << "-";
			}
			cout << endl;
		}
			int count1 = 0;
			for (int j = 0; j < srdstv; j++)
			{
				if (arraymatr[k][i][j] == promezhMax[k][i]) {
					prRez[k][i][count1] = j;
					count1++;
				}
			}
			massindex[count2] = count1;
			count2++;
			max = 0;


		}if (check)cout << endl;
	}
	cout << endl;
	cout << endl;
	sortOfMassiveIndex(massindex);
	req(massindex, prRez, 0, 0, Arr);
	for (int i = 0; i < kolvo; i++)
	{
		Arr[i].sum = promezhMax[0][srdstv - 1];
	}
	cout << "Суммарная ожидаемая прибыль = " << promezhMax[0][srdstv - 1] << endl;
	cout << "\nОптимальные планы по предприятиям: \n";
	cout << "Открыть подсказку?(1/0): ";
	bool podskazka;
	cin >> podskazka;
	if (podskazka)cout << "\nВ каждой пронумерованной строке есть последовательность чисел, которая характеризует план.\nКаждый элемент последовательности указывает количество инвестируемых средств в предприятие под определенным номером.\n\n";
	if (prd < 34) {
		cout << "№  ";
		for (int j = 0; j < prd; j++)
		{
			//if (Arr[i].posl[j] != 65021)
			cout << setw(4) << j + 1 << " ";
		}
		cout << endl << endl;
	}
	for (int i = 0; i < kolvo; i++)
	{
		cout << i + 1 << ". ";
		for (int j = 0; j < prd; j++)
		{
			//if (Arr[i].posl[j] != 65021)
			cout << setw(4) << Arr[i].posl[j] << " ";
		}
		cout << endl << endl;

	}
	cout << "Добавить результаты в файл?(1/0): ";
	bool rezultati;
	cin >> rezultati;
	if (rezultati) {
		ofstream fout("Rezultati.txt", ios_base::app);
		if (!fout.is_open()) // если файл не открыт
			cout << "Файл не может быть открыт!\n"; // сообщить об этом
		else {

			fout << "Cуммарная ожидаемая прибыль " << promezhMax[0][srdstv - 1] << endl;
			fout << "Кол-во средств " << srdstv - 1 << endl;
			fout << "Кол-во предприятий " << prd << endl;
			fout << "Кол-во решений " << kolvo << endl;
			if (prd < 34) {
				fout << "№  ";
				for (int j = 0; j < prd; j++)
				{
					//if (Arr[i].posl[j] != 65021)
					fout << setw(4) << j + 1 << " ";
				}
				fout << endl;
			}

			for (int i = 0; i < kolvo; i++)
			{
				fout << i + 1 << ". ";
				for (int j = 0; j < prd; j++)
				{

					fout << setw(4) << Arr[i].posl[j] << " ";
				}
				fout << endl;

			}
		}
		fout.close();

	}
	kolvo = 0;
	cout << endl;
	cout << endl;

	for (int i = 0; i < prd; i++) {
		for (int j = 0; j < srdstv; j++) {
			delete[] prRez[i][j];
		}
		delete[] prRez[i];
	}
	delete[] prRez;
	for (int i = 0; i < prd; i++) {
		for (int j = 0; j < srdstv; j++) {
			delete[] arraymatr[i][j];
		}
		delete[] arraymatr[i];
	}
	delete[] arraymatr;
	for (int i = 0; i < prd; i++)
		delete[] promezhMax[i];
	delete[] promezhMax;
	for (int i = 0; i < prd; i++)
		delete[] matr[i];
	delete[] matr;
	delete[] massindex;
	check = 1;
	
	while (check) {
		cout << "Для выхода из программы введите 0, чтобы выйти в меню введите 1:   ";
		cin >> f;
		if (f == '0' || f == '1')check = 0;

	}
	
	if (f == '0')return 1;
	else return 0;
	

}
bool ReshenieRandom()
{

	cout << "  \n\n\n       Задача:\n\n\n     Совет директоров фирмы рассматривает предложения относительно прироста производственных мощностей для увеличения выпуска однородной продукции\n     на n предприятиях принадлежащих фирме.Для модернизации предприятий предложено инвестировать средства в объеме X усл.ден.ед. с дискретностью \n     1 усл.ден.ед. Прирост выпуска продукции зависит от выделенной суммы ,а его значения даны предприятиями и содержатся в таблице. Найти\n     распределение инвестиций между предприятиями,обеспечивающее фирме максимальный прирост продукции, при чем на одно предприятие можно\n     осуществить только одну инвестицию.\n\n\n";


	bool check = 1;
	while (check)
	{
		cout << "\n     Введите N(>=3) кол-во предприятий:  "; cin >> prd;
		if (prd >= 3 && prd <= 600) check = 0;
		else cout << "Введите число больше 2 и меньше 600: ";
	}

	while (!check) {
		cout << "\n     Введите X объём инвестируемых средств:  "; cin >> srdstv; cout << "\n";
		srdstv++;
		if (srdstv <= 600 && srdstv >= 0) check = 1;
		else cout << "Введите неотрицательное число  меньше 600: ";
	}


	//cout << "\n     Поочерёдно введите приросты выпуска продукции предприятий:\n";

	unsigned short** matr = new unsigned short* [prd];//матрица с введеными данными где строки средства, а предприятия столбцы
	for (int i = 0; i < prd; i++) matr[i] = new unsigned short[srdstv];

	unsigned short*** arraymatr = new unsigned short** [prd];//матрицы для решений
	for (int i = 0; i < prd; i++)
	{
		arraymatr[i] = new unsigned short* [srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			arraymatr[i][j] = new unsigned short[srdstv];
			for (int k = 0; k < srdstv; k++)
				arraymatr[i][j][k] = 0;
		}
	}

	unsigned short*** prRez = new unsigned short** [prd];//промежуточный результат
	for (int i = 0; i < prd; i++)
	{
		prRez[i] = new unsigned short* [srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			prRez[i][j] = new unsigned short[srdstv];
			for (int k = 0; k < srdstv; k++)
				prRez[i][j][k] = 0;
		}
	}
	unsigned short** promezhMax = new unsigned short* [prd];//промежуточный результат
	for (int i = 0; i < prd; i++)
	{
		promezhMax[i] = new unsigned short[srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			promezhMax[i][j] = 0;
		}
	}
	

	int max = 0;
	unsigned short* massindex = new unsigned short[prd * srdstv];
	int count2 = 0;

	srand(time(0));
	for (int i = 0; i < prd; i++)
	{
		matr[i][0] = 0;
		matr[i][1] = 10 + rand() % 60;
		for (int j = 2; j < srdstv; j++)
		{

			matr[i][j] = matr[i][j - 1] + 1 + rand() % 20;// Заполнение массива случайными возрастающими числами 
		}
	}
	system("cls");
	cout << "  \n\n\n       Задача:\n\n\n     Совет директоров фирмы рассматривает предложения относительно прироста производственных мощностей для увеличения выпуска однородной продукции\n     на n предприятиях принадлежащих фирме.Для модернизации предприятий предложено инвестировать средства в объеме X усл.ден.ед. с дискретностью \n     1 усл.ден.ед. Прирост выпуска продукции зависит от выделенной суммы ,а его значения даны предприятиями и содержатся в таблице. Найти\n     распределение инвестиций между предприятиями,обеспечивающее фирме максимальный прирост продукции, при чем на одно предприятие можно\n     осуществить только одну инвестицию.\n\n\n";
	if (prd < 11 && prd >= 3) {
		cout << "     Исходная матрица: \n\n\n     ";

		for (int i = 0; i < 16; i++)
			cout << "*";
		if (prd / 2 != 0)
		{
			for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		}
		else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";

		cout << "\n     | Инвестиции, |";


		cout << setiosflags(ios::left) << setw(13 * prd - 1) << "Прирост выпуска продукции, усл.ден.ед." << setiosflags(ios::right);

		cout << setw(1) << "|" << '\n';
		cout << "     |             |";
		for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		cout << "|\n";
		cout << "     | усл.ден.ед. |";
		for (int i = 0; i < prd; i++)cout << " g" << setiosflags(ios::left) << setw(6) << i + 1 << "(x) |";//11
		cout << endl << "     ";
		for (int i = 0; i < 16; i++)
			cout << "*";
		if (prd / 2 != 0)
		{
			for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		}
		else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";
		cout << endl;
		for (int i = 0; i < srdstv; i++)
		{
			cout << "     |  " << setw(9) << i;
			cout << "  |";
			for (int j = 0; j < prd; j++)
			{
				cout << "  " << setw(8) << matr[j][i];
				cout << "  |";
			}
			cout << endl << "     ";
			for (int i = 0; i < 16; i++)
				cout << "*";
			if (prd / 2 != 0)
			{
				for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
			}
			else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";
			cout << endl;

		}
	}
	else if (prd > 11) cout << "     Исходную матрицу невозможно вывести, она не влезает на ширину экрана";


	cout << endl;
	if (srdstv < 18) {
		cout << "     Вывести матрицы решений?:";
		cout << endl << "     1. Да        0.Нет    :";
		cin >> check;
	}
	else check = 0;
	cout << "\n\n\n";
	for (int k = prd - 1; k > -1; k--)
	{
		if (check) {
			cout << "     Шаг №" << k + 1;
		
			cout << "      Средства|";
			for (int j = 0; j < srdstv; j++) {
				cout << "x" << setiosflags(ios::left) << setw(6) << j << setiosflags(ios::right) << "|";
			}
		cout << endl;
		cout << "                 --------";
		for (int j = 0; j < srdstv * 8; j++)
		{
			cout << "-";
		}
		}
		cout << endl;
		for (int i = 0; i < srdstv; i++)
		{
			if (check)cout << "                     " << setw(3) << i << " |";
			int count = 0;
			for (int j = 0; j < srdstv; j++)
			{

				if (k != prd - 1)
				{
					if (i == j)
					{
						arraymatr[k][i][j] = matr[k][i];
						if (arraymatr[k][i][j] > max) { max = arraymatr[k][i][j]; }
					}
					else {
						if (j <= i)
						{
							if (j < i) {
								arraymatr[k][i][j] = matr[k][j] + promezhMax[k + 1][i - count];
								count++;
							}
							if (arraymatr[k][i][j] > max) { max = arraymatr[k][i][j]; }


						}
					}
					promezhMax[k][i] = max;

				}
				else { arraymatr[k][i][i] = matr[k][i]; promezhMax[k][i] = matr[k][i]; prRez[k][i][0] = i; }
				if (check)cout << setw(7) << arraymatr[k][i][j] << "|";


			}
			if (check) {
				cout << endl;
				cout << "                 --------";
				for (int j = 0; j < srdstv * 8; j++)
				{
					cout << "-";
				}
				cout << endl;
			}
			int count1 = 0;
			for (int j = 0; j < srdstv; j++)
			{
				if (arraymatr[k][i][j] == promezhMax[k][i]) {
					prRez[k][i][count1] = j;
					count1++;
				}
			}
			massindex[count2] = count1;
			count2++;
			max = 0;


		}if (check)cout << endl;
	}
	cout << endl;
	cout << endl;
	


	
	sortOfMassiveIndex(massindex);
	cout << endl;
	


	cout << endl;
	cout << endl;

	req(massindex, prRez, 0, 0, Arr);
	for (int i = 0; i < kolvo; i++)
	{
		Arr[i].sum = promezhMax[0][srdstv - 1];
	}
	cout << "Суммарная ожидаемая прибыль = " << promezhMax[0][srdstv - 1] << endl;
	cout << "\nОптимальные планы по предприятиям: \n";
	cout << "Открыть подсказку?(1/0): ";
	bool podskazka;
	cin >> podskazka;
	if (podskazka)cout << "\nВ каждой пронумерованной строке есть последовательность чисел, которая характеризует план.\nКаждый элемент последовательности указывает количество инвестируемых средств в предприятие под определенным номером.\n\n";
	if (prd < 34) {
		cout << "№  ";
		for (int j = 0; j < prd; j++)
		{
			//if (Arr[i].posl[j] != 65021)
			cout << setw(4) << j + 1 << " ";
		}
		cout << endl << endl;
	}
	for (int i = 0; i < kolvo; i++)
	{
		cout << i + 1 << ". ";
		for (int j = 0; j < prd; j++)
		{
			//if (Arr[i].posl[j] != 65021)
			cout <<setw(4)<< Arr[i].posl[j] << " ";
		}
		cout << endl << endl;

	}
	cout << "Добавить результаты в файл?(1/0): ";
	bool rezultati;
	cin >> rezultati;
	if (rezultati) {
		ofstream fout("Rezultati.txt", ios_base::app);
		if (!fout.is_open()) // если файл не открыт
			cout << "Файл не может быть открыт!\n"; // сообщить об этом
		else {
			
			fout <<"Cуммарная ожидаемая прибыль "<<promezhMax[0][srdstv - 1] << endl;
			fout <<"Кол-во средств "<<srdstv - 1<<endl;
			fout << "Кол-во предприятий " << prd << endl;
			fout <<"Кол-во решений "<<kolvo << endl;
			if (prd < 34) {
				fout << "№  ";
				for (int j = 0; j < prd; j++)
				{
					//if (Arr[i].posl[j] != 65021)
					fout << setw(4) << j + 1 << " ";
				}
				fout << endl;
			}
			for (int i = 0; i < kolvo; i++)
			{
				fout << i + 1 << ". ";
				for (int j = 0; j < prd; j++)
				{

					fout <<setw(4)<< Arr[i].posl[j] << " ";
				}
				fout << endl;

			}
		}
		fout.close();

	}

	for (int i = 0; i < prd; i++) {
		for (int j = 0; j < srdstv; j++) {
			delete[] prRez[i][j];
		}
		delete[] prRez[i];
	}
	delete[] prRez;
	for (int i = 0; i < prd; i++) {
		for (int j = 0; j < srdstv; j++) {
			delete[] arraymatr[i][j];
		}
		delete[] arraymatr[i];
	}
	delete[] arraymatr;
	for (int i = 0; i < prd; i++)
		delete[] promezhMax[i];
	delete[] promezhMax;
	for (int i = 0; i < prd; i++)
		delete[] matr[i];
	delete[] matr;
	delete[] massindex;

	cout << endl;
	cout << endl;
	kolvo = 0;
	char f;
	check = 1;

	while (check) {
		cout << "Для выхода из программы введите 0, чтобы выйти в меню введите 1:   ";
		cin >> f;
		if (f == '0' || f == '1')check = 0;

	}

	if (f == '0')return 1;
	else return 0;

}
bool ResheniePrimer()
{
	srdstv = 6; prd = 4;
	cout << "  \n\n\n       Задача:\n\n\n     Совет директоров фирмы рассматривает предложения относительно прироста производственных мощностей для увеличения выпуска однородной продукции\n     на n предприятиях принадлежащих фирме.Для модернизации предприятий предложено инвестировать средства в объеме X усл.ден.ед. с дискретностью \n     1 усл.ден.ед. Прирост выпуска продукции зависит от выделенной суммы ,а его значения даны предприятиями и содержатся в таблице. Найти\n     распределение инвестиций между предприятиями,обеспечивающее фирме максимальный прирост продукции, при чем на одно предприятие можно\n     осуществить только одну инвестицию.\n\n\n";
	cout << " \n   При 3 предприятиях и кол-вам инвестируемых средств равным 5 и исходной матрице :\n";

	bool check = 1;
	

	unsigned short** matr = new unsigned short* [prd];//матрица с введеными данными где строки средства, а предприятия столбцы
	for (int i = 0; i < prd; i++) matr[i] = new unsigned short[srdstv];

	unsigned short*** arraymatr = new unsigned short** [prd];//матрицы для решений
	for (int i = 0; i < prd; i++)
	{
		arraymatr[i] = new unsigned short* [srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			arraymatr[i][j] = new unsigned short[srdstv];
			for (int k = 0; k < srdstv; k++)
				arraymatr[i][j][k] = 0;
		}
	}

	unsigned short*** prRez = new unsigned short** [prd];//промежуточный результат
	for (int i = 0; i < prd; i++)
	{
		prRez[i] = new unsigned short* [srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			prRez[i][j] = new unsigned short[srdstv];
			for (int k = 0; k < srdstv; k++)
				prRez[i][j][k] = 0;
		}
	}
	unsigned short** promezhMax = new unsigned short* [prd];//промежуточный результат
	for (int i = 0; i < prd; i++)
	{
		promezhMax[i] = new unsigned short[srdstv];
		for (int j = 0; j < srdstv; j++)
		{
			promezhMax[i][j] = 0;
		}
	}
	

	int max = 0;
	unsigned short* massindex = new unsigned short[prd * srdstv];
	int count2 = 0;
	
	
	matr[0][0] = 0; matr[1][0] = 0; matr[2][0] = 0; matr[3][0] = 0;
	matr[0][1] = 8; matr[1][1] = 10; matr[2][1] = 12; matr[3][1] = 11;
	matr[0][2] = 16; matr[1][2] = 20; matr[2][2] = 21; matr[3][2] = 23;
	matr[0][3] = 25; matr[1][3] = 28; matr[2][3] = 27; matr[3][3] = 30;
	matr[0][4] = 36; matr[1][4] = 40; matr[2][4] = 38; matr[3][4] = 37;
	matr[0][5] = 44; matr[1][5] = 48; matr[2][5] = 50; matr[3][5] = 51;
	

	system("cls");
	cout << "  \n\n\n       Задача:\n\n\n     Совет директоров фирмы рассматривает предложения относительно прироста производственных мощностей для увеличения выпуска однородной продукции\n     на n предприятиях принадлежащих фирме.Для модернизации предприятий предложено инвестировать средства в объеме X усл.ден.ед. с дискретностью \n     1 усл.ден.ед. Прирост выпуска продукции зависит от выделенной суммы ,а его значения даны предприятиями и содержатся в таблице. Найти\n     распределение инвестиций между предприятиями,обеспечивающее фирме максимальный прирост продукции, при чем на одно предприятие можно\n     осуществить только одну инвестицию.\n\n\n";
	cout << " \n   При 3 предприятиях и кол-вам инвестируемых средств равным 5 и исходной матрице :\n";
	if (prd < 11 && prd >= 3) {
		cout << "     Исходная матрица: \n\n\n     ";

		for (int i = 0; i < 16; i++)
			cout << "*";
		if (prd / 2 != 0)
		{
			for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		}
		else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";

		cout << "\n     | Инвестиции, |";


		cout << setiosflags(ios::left) << setw(13 * prd - 1) << "Прирост выпуска продукции, усл.ден.ед." << setiosflags(ios::right);

		cout << setw(1) << "|" << '\n';

		cout << "     |             |";

		for (int i = 0; i < 13 * prd - 1; i++) cout << "*";


		cout << "|\n";


		cout << "     | усл.ден.ед. |";
		for (int i = 0; i < prd; i++)cout << " g" << setiosflags(ios::left) << setw(6) << i + 1 << "(x) |";//11
		cout << endl << "     ";

		for (int i = 0; i < 16; i++)
			cout << "*";
		if (prd / 2 != 0)
		{
			for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		}
		else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";
		cout << endl;
		for (int i = 0; i < srdstv; i++)
		{
			cout << "     |  " << setw(9) << i;
			cout << "  |";
			for (int j = 0; j < prd; j++)
			{
				cout << "  " << setw(8) << matr[j][i];
				cout << "  |";

			}
			cout << endl << "     ";
			for (int i = 0; i < 16; i++)
				cout << "*";
			if (prd / 2 != 0)
			{
				for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
			}
			else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";

			cout << endl;

		}
	}
	else if (prd > 11) cout << "     Исходную матрицу невозможно вывести, она не влезает на ширину экрана";


	cout << endl;

	cout << "     Вывести матрицы решений?:";
	cout << endl << "     1. Да        0.Нет    :";
	cin >> check;


	cout << "\n\n\n";
	for (int k = prd - 1; k > -1; k--)
	{
		if (check) cout << "     Шаг №" << k + 1;
		if (check) {
			cout << "      Средства|";
			for (int j = 0; j < srdstv; j++) {
				cout << "x" << setiosflags(ios::left) << setw(6) << j << setiosflags(ios::right) << "|";
			}

			cout << endl;
			cout << "                 --------";
			for (int j = 0; j < srdstv * 8; j++)
			{
				cout << "-";
			}
		}
		cout << endl;
		for (int i = 0; i < srdstv; i++)
		{


			if (check)cout << "                     " << setw(3) << i << " |";

			int count = 0;
			for (int j = 0; j < srdstv; j++)
			{

				if (k != prd - 1)
				{
					if (i == j)
					{
						arraymatr[k][i][j] = matr[k][i];
						if (arraymatr[k][i][j] > max) { max = arraymatr[k][i][j]; }
					}
					else {
						if (j <= i)
						{
							if (j < i) {
								arraymatr[k][i][j] = matr[k][j] + promezhMax[k + 1][i - count];
								count++;
							}
							if (arraymatr[k][i][j] > max) { max = arraymatr[k][i][j]; }


						}
					}
					promezhMax[k][i] = max;

				}
				else { arraymatr[k][i][i] = matr[k][i]; promezhMax[k][i] = matr[k][i]; prRez[k][i][0] = i; }
				if (check)cout << setw(7) << arraymatr[k][i][j] << "|";


			}
			if (check) {
				cout << endl;
				cout << "                 --------";
				for (int j = 0; j < srdstv * 8; j++)
				{
					cout << "-";
				}
				cout << endl;
			}
			int count1 = 0;
			for (int j = 0; j < srdstv; j++)
			{
				if (arraymatr[k][i][j] == promezhMax[k][i]) {
					prRez[k][i][count1] = j;
					count1++;
				}
			}
			massindex[count2] = count1;
			count2++;
			max = 0;


		}if (check)cout << endl;
	}
	cout << endl;
	cout << endl;
	

	
	cout << endl;
	
	sortOfMassiveIndex(massindex);
	


	cout << endl;
	cout << endl;

	req(massindex, prRez, 0, 0, Arr);
	for (int i = 0; i < kolvo; i++)
	{
		Arr[i].sum = promezhMax[0][srdstv - 1];
	}
	cout << "Суммарная ожидаемая прибыль = " << promezhMax[0][srdstv - 1] << endl;
	cout << "\nОптимальные планы по предприятиям: \n";
	cout << "Открыть подсказку?(1/0): ";
	bool podskazka;
	cin >> podskazka;
	if (podskazka)cout << "\nВ каждой пронумерованной строке есть последовательность чисел, которая характеризует план.\nКаждый элемент последовательности указывает количество инвестируемых средств в предприятие под определенным номером.\n\n";
	if (prd < 34) {
		cout << "№  ";
		for (int j = 0; j < prd; j++)
		{
			//if (Arr[i].posl[j] != 65021)
			cout << setw(4) << j + 1 << " ";
		}
		cout << endl << endl;
	}
	for (int i = 0; i < kolvo; i++)
	{
		cout << i + 1 << ". ";
		for (int j = 0; j < prd; j++)
		{
			//if (Arr[i].posl[j] != 65021)
			cout << setw(4) << Arr[i].posl[j] << " ";
		}
		cout << endl << endl;

	}
	
	cout << "Добавить результаты в файл?(1/0): ";
	bool rezultati;
	cin >> rezultati;
	if (rezultati) {
		ofstream fout("Rezultati.txt", ios_base::app);
		if (!fout.is_open()) // если файл не открыт
			cout << "Файл не может быть открыт!\n"; // сообщить об этом
		else {

			fout << "Cуммарная ожидаемая прибыль " << promezhMax[0][srdstv - 1] << endl;
			fout << "Кол-во средств " << srdstv - 1 << endl;
			fout << "Кол-во предприятий " << prd << endl;
			fout << "Кол-во решений " << kolvo << endl;
			if (prd < 34) {
				fout << "№  ";
				for (int j = 0; j < prd; j++)
				{
					//if (Arr[i].posl[j] != 65021)
					fout << setw(4) << j + 1 << " ";
				}
				fout << endl;
			}
			

			for (int i = 0; i < kolvo; i++)
			{
				fout << i + 1 << ". ";
				for (int j = 0; j < prd; j++)
				{

					fout << setw(4) << Arr[i].posl[j] << " ";
				}
				fout << endl;

			}
		}
		fout.close();
	}
	for (int i = 0; i < prd; i++) {
		for (int j = 0; j < srdstv; j++) {
			delete[] prRez[i][j];
		}
		delete[] prRez[i];
	}
	delete[] prRez;
	for (int i = 0; i < prd; i++) {
		for (int j = 0; j < srdstv; j++) {
			delete[] arraymatr[i][j];
		}
		delete[] arraymatr[i];
	}
	delete[] arraymatr;
	for (int i = 0; i < prd; i++)
		delete[] promezhMax[i];
	delete[] promezhMax;
	for (int i = 0; i < prd; i++)
		delete[] matr[i];
	delete[] matr;
	delete[] massindex;


	cout << endl;
	cout << endl;
	check = 1;
	kolvo = 0;
	char f;
	while (check) {
		cout << "Для выхода из программы введите 0, чтобы выйти в меню введите 1:   ";
		cin >> f;
		if (f == '0' || f == '1')check = 0;

	}

	if (f == '0')return 1;
	else return 0;


}
char mainScreen()
{

	for (int i = 0; i < 6; i++)
		cout << '\n';
	for (int i = 0; i < 75; i++)
		cout << " ";
	cout << "Курсовая работа по теме:\n";
	for (int i = 0; i < 60; i++)
		cout << " ";
	cout << "Программная реализация задачи о распределении инвестиций\n";
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
	cout << "5.Выход из программы\n\n";
	for (int i = 0; i < 60; i++)
		cout << " ";
	cout << "Выберите 1, 2, 3, 4 или 5:       ";
	char k; cin >> k;
	return(k);
}
