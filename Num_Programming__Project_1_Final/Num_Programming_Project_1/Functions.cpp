#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

void Matrix::init()
{
	cout << "Please enter the number of equations (n <= 10): ";
	cin >> numOfEquations;
	while (!numOfEquations <= 10)
	{
		cout << "Invalid number of equations. Try again." << endl;
		cin >> numOfEquations;
	}
	cout << endl;

	cout << "Enter the coefficients for the equations (x, y, z, b): " << endl;

	a = new int* [numOfEquations];
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << "Row " << i << ": ";
		a[i] = new int[4];
		cin >> a[i][0];
		cin >> a[i][1];
		cin >> a[i][2];
		cin >> a[i][3];
	}

	indexVector = new int[numOfEquations];
	for (int i = 0; i < numOfEquations; i++)
	{
		indexVector[i] = i;
	}
	scaleVector = new int[numOfEquations];
	cout << endl;
}

void Matrix::printMatrix()
{
	cout << "Printing Matrix" << endl;
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << "Row " << i << ": ";
		cout << a[i][0] << " ";
		cout << a[i][1] << " ";
		cout << a[i][2] << " ";
		cout << a[i][3] << " ";
		cout << endl;
	}

	cout << "Printing indexVector" << endl;
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << indexVector[i] << " ";
	}

	cout << "Printing scaleVector" << endl;
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << scaleVector[i] << " ";
	}
	cout << endl;
}

Matrix::~Matrix()
{
	deleteMatrix();
}

void Matrix::deleteMatrix()
{
	for (int i = 0; i < numOfEquations; i++)
	{
		delete[] a[i];
	}
	delete[] a;
}