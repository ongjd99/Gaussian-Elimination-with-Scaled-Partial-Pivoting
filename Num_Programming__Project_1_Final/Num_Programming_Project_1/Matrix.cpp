/*
	Ong, Johnny

	September 30, 2020

	CS 3010.01 Numerical Methods
	Programming Project 1
*/

#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Matrix::Matrix()
{
	matrix = new double* [1];
	numOfEquations = 0;
}

void Matrix::init()
{
	cout << "Please enter the number of equations (n <= 10): ";
	numOfEquations = verifyInput();
	while (!(numOfEquations <= 10 && numOfEquations > 0))
	{
		cout << "Invalid number of equations. Try again." << endl;
		numOfEquations = verifyInput();
	}
	cout << endl;

	cout << "Enter the coefficients for the equations (x1, x2, x3, x4,...,xn, b): " << endl;

	matrix = new double* [numOfEquations];
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << "Row " << i << ": ";
		int rowSize = numOfEquations + 1;
		matrix[i] = new double[rowSize];
		for (int j = 0; j < rowSize; j++)
		{
			matrix[i][j] = verifyInput();
		}
	}

	indexVector.reserve(numOfEquations);
	for (int i = 0; i < numOfEquations; i++)
	{
		indexVector.push_back(i);
	}
	setScaleVector();
	cout << endl;
}

void Matrix::initFile()
{
	cout << "Please enter the number of equations (n <= 10): ";
	numOfEquations = verifyInput();
	while (!(numOfEquations <= 10 && numOfEquations > 0))
	{
		cout << "Invalid number of equations. Try again." << endl;
		numOfEquations = verifyInput();
	}
	cout << endl;

	cout << "Enter filename (including .txt): ";
	string file;
	cin >> file;
	ifstream infile;
	infile.open(file);
	if (infile.fail())
	{
		cout << "Error; File could not be found. Try Again." << endl;
		initFile();
	}

	int data = 0;
	matrix = new double* [numOfEquations];
	while (!infile.eof())
	{
		for (int i = 0; i < numOfEquations; i++)
		{
			cout << "Row " << i << ": ";
			int rowSize = numOfEquations + 1;
			matrix[i] = new double[rowSize];
			for (int j = 0; j < rowSize; j++)
			{
				infile >> data;
				matrix[i][j] = data;
			}
		}
	}

	indexVector.reserve(numOfEquations);
	for (int i = 0; i < numOfEquations; i++)
	{
		indexVector.push_back(i);
	}
	setScaleVector();
	cout << endl;
}

void Matrix::printMatrix(vector<double> modifiedScale)
{
	cout << "Printing Matrix" << endl;
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << "Row " << i << ": ";
		int rowSize = numOfEquations + 1;
		for (int j = 0; j < rowSize; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Printing indexVector" << endl;
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << indexVector[i] << " ";
	}
	cout << endl;

	cout << "Printing scaleVector" << endl;
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << modifiedScale[i] << " ";
	}
	cout << endl;
	cout << endl;
}

void Matrix::setScaleVector()
{
	scaleVector.reserve(numOfEquations);
	for (int i = 0; i < numOfEquations; i++)
	{
		double max = abs(matrix[i][0]);
		for (int j = 1; j < numOfEquations; j++)
		{
			if (max < abs(matrix[i][j]))
			{
				max = abs((matrix[i][j]));
			}
		}
		scaleVector.push_back(max);
	}
}

void Matrix::updateMatrix(int currentIndex)
{
	int row = indexVector.at(currentIndex);
	for (int i = currentIndex + 1; i < numOfEquations; i++)
	{
		double factor = matrix[row][currentIndex] / matrix[indexVector[i]][currentIndex];
		for (int j = currentIndex; j <= numOfEquations; j++)
		{
			matrix[indexVector[i]][j] = matrix[indexVector[i]][j] - (matrix[row][j] / factor);
		}
	}
}

// solve for xn
// multiple all other indices in the same column by xn
// subtract the product by b
// repeat with next column
void Matrix::finalize()
{
	auto revIter = indexVector.crbegin();

	for (int i = 1; i < numOfEquations; i++)
	{
		double b = matrix[*revIter][numOfEquations];
		double xn = b / matrix[*revIter][numOfEquations - i];
		auto revIterCopy = revIter;
		answerVector.push(xn); 
		for (int j = i; j < numOfEquations; j++)
		{
			revIterCopy++;
			matrix[*revIterCopy][numOfEquations - i] *= xn;
			matrix[*revIterCopy][numOfEquations] -= matrix[*revIterCopy][numOfEquations - i];
		}
		revIter++;
	}
	answerVector.push(matrix[*revIter][numOfEquations] / matrix[*revIter][0]);
}

void Matrix::printResults() 
{
	int i = 0;
	while (!answerVector.empty())
	{
		if (i < 3)
		{
			cout << char(i + 120) << ": " << answerVector.top() << endl;
		}
		else
		{
			cout << char(i + 94) << ": " << answerVector.top() << endl;
		}
		answerVector.pop();
		i++;
	}
}

int Matrix::verifyInput()
{
	int input = 0;
	while (!(cin >> input))
	{
		cout << "Error: Invalid character" << endl;
		cin.clear();
		cin.ignore(1, ' ');
	}
	
	return input;
}

// Couldn't figure out how to overload operator[][] so I went the easy way
double Matrix::at(int i, int j)
{
	return matrix[i][j];
}


int Matrix::getNumOfEquations()
{
	return numOfEquations;
}


vector<int>& Matrix::getIndexVector()
{
	return indexVector;
}

/*
	We want to keep the original scale vector in order to determine
	our new index vector at each stage. Therefore, by not returning 
	a reference we can perform calculations on a copy.
*/
vector<double> Matrix::getScaleVector()
{
	return scaleVector;
}

/*
	Once we figured out our index vector for that stage of the matrix,
	we want to update our scale vector with that index = 0 to say we
	are done with that row. Returning the reference will accomplish that.
*/
vector<double>& Matrix::getScaleVectorRef()
{
	return scaleVector;
}

 
Matrix::~Matrix()
{
	deleteMatrix();
}

void Matrix::deleteMatrix()
{
	for (int i = 0; i < numOfEquations; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
}