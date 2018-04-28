#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>


using namespace std;

unsigned long long multiply(long x, long res[], long res_size), recursiveMultiply(long x, long res[], long res_size, long n);
void factorial(long n), recursiveFactorial(long n);
const long max = 100000000;

int main() {
	recursiveFactorial(100000);
	return 0;
}

void factorial(long n)
{
	long overflow[max];
	//Instantiate the array which will hold overflows of the main factorial number
	overflow[0] = 1;
	long overflow_size = 1;

	//Iterative factorial approach (calls function multiply however is still loop-based)
	for (long x = 1; x <= n; x++){
		overflow_size = multiply(x, overflow, overflow_size);
	}

	//Create output information
	ofstream outputFile;
	outputFile.open("C:\\Ben\\Factorial - " + to_string(n) + ".txt");

	//Print the results of the loop
	for (long i = overflow_size - 1; i >= 0; i--){
		outputFile << overflow[i];
	}

	outputFile.close();
}

// Takes res[] as input (representation/number of digits) and multiplies it by the long x
unsigned long long multiply(long x, long res[], long res_size)
{
	/*Starting some GCSE maths*/
	long carry = 0;  

	// For each individual integer multiply by x
	for (long i = 0; i<res_size; i++)
	{
		long prod = res[i] * x + carry;
		/*New last digit*/
		res[i] = prod % 10;
		/*Overflow stored by carry*/
		carry = prod / 10;
	}

	/*Move carry to the array and free buffers*/
	while (carry)
	{
		res[res_size] = carry % 10;
		carry = carry / 10;
		res_size++;
	}
	return res_size;
}

void recursiveFactorial(long n)
{
	long overflow[max];
	//Instantiate the array which will hold overflows of the main factorial number
	overflow[0] = 1;
	long overflow_size = 1;


	overflow_size = recursiveMultiply(1, overflow, overflow_size, n);

	//Create output information
	ofstream outputFile;
	outputFile.open("C:\\Ben\\Factorial - " + to_string(n) + ".txt");

	//Print the results of the loop
	for (long i = overflow_size - 1; i >= 0; i--) {
		outputFile << overflow[i];
	}

	outputFile.close();
}

// Takes res[] as input (representation/number of digits) and multiplies it by the long x
unsigned long long recursiveMultiply(long x, long res[], long res_size, long n)
{
	/*Starting some GCSE maths*/
	long carry = 0;

	// For each individual integer multiply by x
	for (long i = 0; i<res_size; i++)
	{
		long prod = res[i] * x + carry;
		/*New last digit*/
		res[i] = prod % 10;
		/*Overflow stored by carry*/
		carry = prod / 10;
	}

	/*Move carry to the array and free buffers*/
	while (carry)
	{
		res[res_size] = carry % 10;
		carry = carry / 10;
		res_size++;
	}

	return (x == n) ? res_size : recursiveMultiply((x+1), res, res_size, n);
}
