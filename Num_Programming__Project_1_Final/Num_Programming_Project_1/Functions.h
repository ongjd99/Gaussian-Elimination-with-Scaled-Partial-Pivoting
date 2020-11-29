#pragma once

class Matrix
{
public:
	~Matrix();
	void init();
	void printMatrix();
	void deleteMatrix();

private:
	int** a;
	int numOfEquations;
	int* indexVector;
	int* scaleVector;
};
