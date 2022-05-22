//ÖZGE KATIRCI   MELÝSA DEMÝRHAN
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

bool pointControl(char** matrix, int, int, bool**);
int patternDetecting(char** matrix, int, int, bool**);

int point = 0;
int SumRow, SumColumn;
int SizeOfRow, SizeOfColumn;

int main() {
	char** A;
	bool** VisitedPoint;
	string NameOfFile;
	int patternCount = 0;
	float CenterRow, CenterColumn;

	cout << "Enter the file name: ";
	getline(cin, NameOfFile);

	fstream file(NameOfFile, ios::in);

	if (!file)
	{
		cout << "ERROR!";
		exit(0);
	}

	file >> SizeOfRow;
	file >> SizeOfColumn;
	file.ignore();

	A = new char* [SizeOfRow];
	for (int i = 0; i < SizeOfRow; i++)
	{
		A[i] = new char[SizeOfColumn];
	}

	VisitedPoint = new bool* [SizeOfRow];
	for (int i = 0; i < SizeOfRow; i++)
	{
		VisitedPoint[i] = new bool[SizeOfColumn];
	}
	for (int i = 0; i < SizeOfRow; i++)
	{
		for (int j = 0; j < SizeOfColumn; j++)
		{
			VisitedPoint[i][j] = 0;
		}
	}

	int k = 0;
	cout << "  ";
	for (int i = 0; i < SizeOfColumn; i++)
	{
		if (k > 9)
		{
			k = 0;
		}
		cout << k;
		k++;
	}
	cout << endl << " +";
	for (int i = 0; i < SizeOfColumn; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;

	for (int i = 0; i < SizeOfRow; i++)
	{
		for (int j = 0; j <= SizeOfColumn; j++)
		{
			file.read((char*)&A[i][j], sizeof(char));
		}
	}
	
	k = 0;
	for (int i = 0; i < SizeOfRow; i++)
	{
		if (k > 9)
		{
			k = 0;
		}
		cout << k << "|";
		for (int j = 0; j < SizeOfColumn; j++)
		{
			cout << A[i][j];
		}
		cout << "|" << k;
		k++;
		cout << endl;
	}

	cout << " +";
	for (int i = 0; i < SizeOfColumn; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;

	k = 0;
	cout << "  ";
	for (int i = 0; i < SizeOfColumn; i++)
	{
		if (k > 9)
		{
			k = 0;
		}
		cout << k;
		k++;
	}

	cout << endl << endl;
	cout << "+------+------------+---------+------------+" << endl;
	cout << "| BLOB | NoOfPixels | CoM Row | CoM Column |" << endl;
	cout << "+------+------------+---------+------------+" << endl;

	for (int i = 0; i < SizeOfRow; i++)
	{
		for (int j = 0; j < SizeOfColumn; j++)
		{
			if (A[i][j] == 'x' && !VisitedPoint[i][j])
			{
				SumColumn = j;
				SumRow = i;

				point = patternDetecting(A, i, j,VisitedPoint);

				CenterRow = (float)SumRow / (float)(point + 1);
				CenterColumn = (float)SumColumn / (float)(point + 1);

				patternCount++;
				printf("|%6d|%12d|%9.2f|%12.2f|", patternCount, point + 1, CenterRow, CenterColumn);
				cout << endl;
				point = 0;
			}
		}
	}
	cout << "+------+------------+---------+------------+" << endl;

	file.close();
	delete[] A;
	delete[] VisitedPoint;

	system("pause");
}
bool pointControl(char** A, int row, int col, bool** VisitedPoint) {

	if (row >= 0 && row < SizeOfRow && col <= SizeOfColumn && col >= 0 && !VisitedPoint[row][col] && A[row][col] == 'x')
		return true;
	else
		return false;
}
int patternDetecting(char** A, int row, int col, bool** VisitedPoint) {
	int i;
	int ArrayR[4] = { -1,0,1,0 };
	int ArrayC[4] = { 0,-1,0,1 };

	VisitedPoint[row][col] = true;

	for (i = 0; i < 4; i++)
	{
		if (pointControl(A, row + ArrayR[i], col + ArrayC[i],VisitedPoint) && A[row + ArrayR[i]][col + ArrayC[i]] == 'x')
		{
			patternDetecting(A, row + ArrayR[i], col + ArrayC[i],VisitedPoint);
			point++;
			SumRow += row + ArrayR[i];
			SumColumn += col + ArrayC[i];
		}
	}
	return point;
}