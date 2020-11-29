/*
	Ong, Johnny

	September 30, 2020

	CS 3010.01 Numerical Methods
	Programming Project 1
*/

#include "Matrix.h"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int main()
{
	/*
		Creating an class object to better work with the data as well as
		encapsulate some of the functions for better debugging.
	*/
	Matrix a;
	cout << "Will you be inputting a txt file? Y/N ";
	char ans;
	cin >> ans;
	cout << endl;
	if (toupper(ans) == 'Y')
	{
		a.initFile();
	}
	else
	{
		a.init();
	}
	a.printMatrix(a.getScaleVector());

	int numOfEquations = a.getNumOfEquations();
	for (int i = 0; i < numOfEquations - 1; i++)
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		vector<double> scaleVector = a.getScaleVector();
		for (int j = 0; j < numOfEquations; j++)
		{
			scaleVector.at(j) = abs(a.at(j, i)) / scaleVector.at(j);
		}

		pair<double, int> largestScaleVector = make_pair(0, 0);
		for (int j = 0; j < numOfEquations; j++)
		{
			if (largestScaleVector.first < scaleVector.at(j) && scaleVector.at(j) <= 1 && scaleVector.at(j) >= 0)
			{
				largestScaleVector.first = scaleVector.at(j);
				largestScaleVector.second = j;
			}
		}

		vector<int>::iterator indexIterator = a.getIndexVector().begin() ;
		int j = i;
		while (j > 0)
		{
			indexIterator++;
			j--;
		}
		vector<int>::iterator indexIteratorSwap = a.getIndexVector().begin();
		while (*indexIteratorSwap != largestScaleVector.second)
		{
			indexIteratorSwap++;
		}
		iter_swap(indexIterator, indexIteratorSwap);
		a.getScaleVectorRef().at(largestScaleVector.second) = 0;

		a.updateMatrix(i);
		a.printMatrix(scaleVector);
	}
	
	a.finalize();
	a.printResults();

	cout << endl;
	system("Pause");

	return 0;
}