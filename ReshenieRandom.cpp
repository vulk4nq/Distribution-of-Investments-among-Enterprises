#include <iostream>
#include <iomanip>
#include <ctime>
#include "Reshenie_s_vvodom.cpp"
using namespace std;



bool ReshenieRandom()
{

	cout << "  \n\n\n       ������:\n\n\n     ����� ���������� ����� ������������� ����������� ������������ �������� ���������������� ��������� ��� ���������� ������� ���������� ���������\n     �� n ������������ ������������� �����.��� ������������ ����������� ���������� ������������� �������� � ������ X ���.���.��. � ������������� \n     1 ���.���.��. ������� ������� ��������� ������� �� ���������� ����� ,� ��� �������� ���� ������������� � ���������� � �������. �����\n     ������������� ���������� ����� �������������,�������������� ����� ������������ ������� ���������, ��� ��� �� ���� ����������� �����\n     ����������� ������ ���� ����������.\n\n\n";


	bool check = 1;
	while (check)
	{
		cout << "\n     ������� N(>=3) ���-�� �����������:  "; cin >> prd;
		if (prd >= 3 && prd <= 600) check = 0;
		else cout << "������� ����� ������ 2 � ������ 600: ";
	}

	while (!check) {
		cout << "\n     ������� X ����� ������������� �������:  "; cin >> srdstv; cout << "\n";
		srdstv++;
		if (srdstv <= 600) check = 1;
		else cout << "������� �����  ������ 600: ";
	}

	cout << "\n     ��������� ������� �������� ������� ��������� �����������:\n";

	unsigned short** matr = new unsigned short* [prd];//������� � ��������� ������� ��� ������ ��������, � ����������� �������
	for (int i = 0; i < prd; i++) matr[i] = new unsigned short[srdstv];

	unsigned short*** arraymatr = new unsigned short** [prd];//������� ��� �������
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

	unsigned short*** prRez = new unsigned short** [prd];//������������� ���������
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
	unsigned short** promezhMax = new unsigned short* [prd];//������������� ���������
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
	cout << "  \n\n\n       ������:\n\n\n     ����� ���������� ����� ������������� ����������� ������������ �������� ���������������� ��������� ��� ���������� ������� ���������� ���������\n     �� n ������������ ������������� �����.��� ������������ ����������� ���������� ������������� �������� � ������ X ���.���.��. � ������������� \n     1 ���.���.��. ������� ������� ��������� ������� �� ���������� ����� ,� ��� �������� ���� ������������� � ���������� � �������. �����\n     ������������� ���������� ����� �������������,�������������� ����� ������������ ������� ���������, ��� ��� �� ���� ����������� �����\n     ����������� ������ ���� ����������.\n\n\n";
	if (prd < 11 && prd >= 3) {
		cout << "     �������� �������: \n\n\n     ";

		for (int i = 0; i < 16; i++)
			cout << "*";
		if (prd / 2 != 0)
		{
			for (int i = 0; i < 13 * prd - 1; i++) cout << "*";
		}
		else for (int i = 0; i < 13 * prd - 3; i++)cout << "*";

		cout << "\n     | ����������, |";


		cout << setiosflags(ios::left) << setw(13 * prd - 1) << "������� ������� ���������, ���.���.��." << setiosflags(ios::right);

		cout << setw(1) << "|" << '\n';

		cout << "     |             |";

		for (int i = 0; i < 13 * prd - 1; i++) cout << "*";


		cout << "|\n";


		cout << "     | ���.���.��. |";
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
	else if (prd > 11) cout << "     �������� ������� ���������� �������, ��� �� ������� �� ������ ������";


	cout << endl;

	cout << "     ������� ������� �������?:";
	cout << endl << "     1. ��        0.���    :";
	cin >> check;


	cout << "\n\n\n";
	for (int k = prd - 1; k > -1; k--)
	{
		if (check) cout << "     ��� �" << k + 1;
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
	cout << endl << "�������� �����" << endl << rez[0].sum;*/
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
	cout << "��� ������ �� ��������� ������� 0, ����� ����� � ���� ������� 1:   ";
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



