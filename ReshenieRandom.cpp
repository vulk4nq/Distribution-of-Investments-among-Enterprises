#include <iostream>
#include <iomanip>
#include <ctime>
#include "Reshenie_s_vvodom.cpp"
using namespace std;



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
		if (srdstv <= 600) check = 1;
		else cout << "Введите число  меньше 600: ";
	}

	cout << "\n     Поочерёдно введите приросты выпуска продукции предприятий:\n";

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
	struct Rezultat {
		unsigned short* posl = new unsigned short[srdstv];
		unsigned short sum;
	}rez[10000];

	int max = 0;
	unsigned short* massindex = new unsigned short[prd * srdstv];
	int count2 = 0;

	srand(time(0));
	for (int i = 0; i < prd; i++)
	{
		matr[i][0] = 0;
		matr[i][1] = 10 + rand() % 20;
		for (int j = 2; j < srdstv; j++)
		{
			
			matr[i][j] = matr[i][j - 1] + 1 + rand() % 20;
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

	cout << "     Вывести матрицы решений?:";
	cout << endl << "     1. Да        0.Нет    :";
	cin >> check;


	cout << "\n\n\n";
	for (int k = prd - 1; k > -1; k--)
	{
		if (check) cout << "     Шаг №" << k + 1;
		if (check) {
			cout << "              |";
			for (int j = 0; j < srdstv; j++) {
				cout << "x" << setiosflags(ios::left) << setw(6) << j << setiosflags(ios::right) << "|";
			}

		}cout << endl;
		cout << "                         ";
		for (int j = 0; j < srdstv * 8; j++)
		{
			cout << "-";
		}
		cout << endl;
		for (int i = 0; i < srdstv; i++)
		{


			if (check)cout << "                         |";

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
			cout << endl;
			cout << "                         ";
			for (int j = 0; j < srdstv * 8; j++)
			{
				cout << "-";
			}
			cout << endl;
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
	int counter = 0;

	/*for (int i = 0; i < massindex[count2]; i++)
	{
		for (int k = 0; k < prd; k++)
		{
			if (k == 0)
			{
				rez[counter].posl[0] = prRez[0][srdstv - 1][0];
				rez[counter].sum = promezhMax[0][srdstv - 1];
			}
			else { int key = 1; int it = i; recursia(); key++; }
		}
				counter++;



	}
	cout << endl << "Итоговая сумма" << endl << rez[0].sum;*/
	cout << endl;
	for (int i = 0; i < srdstv * prd; i++)
	{
		cout << " " << massindex[i];
	}
	sortOfMassiveIndex(massindex);
	cout << endl;
	for (int i = 0; i < srdstv * prd; i++)
	{
		cout << " " << massindex[i];
	}


	cout << endl;
	cout << endl;

	req(massindex, prRez, 0, 0, Arr);
	for (int i = 0; i < kolvo; i++)
	{
		cout << i << ". ";
		for (int j = 0; j < prd; j++)
		{
			if (Arr[i].posl[j] != 65021)
				cout << Arr[i].posl[j] << " ";
		}
		cout << endl;
	}




	cout << endl;
	cout << endl;
	bool flag;
	cout << "Для выхода из программы введите 0, чтобы выйти в меню введите 1:   ";
	cin >> flag;

	return(!flag);

}





/*void recursia(unsigned short*** arrMatrix, unsigned short* massiveindex,const int &count, unsigned short*** promezhRezult,unsigned short** promezhMax,const int &key,const int &it)
{
	for(int i =0;)
	rez[count].posl[key] = promezhRezult[key][srdstv - it][massiveindex[(key + 1) * srdstv - it]];
	recursia(arrMatrix,massiveindex,count,promezhRezult,promezhMax,key,it);
	i

}*/



