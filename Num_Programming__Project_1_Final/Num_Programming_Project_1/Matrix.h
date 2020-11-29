/*
	Ong, Johnny

	September 30, 2020

	CS 3010.01 Numerical Methods
	Programming Project 1
*/

#pragma once

#include <vector>
#include <stack>

class Matrix
{
public:
	Matrix();
	~Matrix();
	void init();
	void initFile();
	void printMatrix(std::vector<double>);
	void deleteMatrix();
	void setScaleVector();
	void updateMatrix(int);
	void finalize();
	void printResults();

	int getNumOfEquations();
	int verifyInput();
	double at(int, int);

	std::vector<int>& getIndexVector();
	std::vector<double> getScaleVector();
	std::vector<double>& getScaleVectorRef();

private:
	double** matrix;
	int numOfEquations;
	std::vector<int> indexVector;
	std::vector<double> scaleVector;
	std::stack<double> answerVector;
};
