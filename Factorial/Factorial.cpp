#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

unsigned long long multiply(long x, long res[], long res_size, long n), recursiveMultiply(long x, long res[], long res_size, long n); 
void factorial(long n), recursiveFactorial(long n), outputToFile(int size, long numberToOutput[], long n);
const long max = 200000000;

int main() {
	int selectedMethod;
	int numberToFactorialise;
	clock_t clockStart;

	while (true)
	{
		system("cls");
		cout << "BSc Computing and Internet Technologies - Advanced Programming A2 - Benjamin Pople" << endl << endl;

		cout << "1. Iterative" << endl;
		cout << "2. Recursive" << endl;
		cout << "Please Select a Factorial Calculation Method (1/2): ";

		cin >> selectedMethod;

		system("cls");

		switch (selectedMethod)
		{
		case(1): {
			//Iterative
			cout << "Please Enter n!: ";
			cin >> numberToFactorialise;
			system("cls");
			clockStart = clock();
			factorial(numberToFactorialise);
			system("cls");
			cout << "Iterative Factorial Calculation\n";
			cout << "-------------------------------\n";
			break;
		}
		case(2): {
			//Recursive
			cout << "Please Enter n!: ";
			cin >> numberToFactorialise;
			system("cls");
			clockStart = clock();
			recursiveFactorial(numberToFactorialise);
			system("cls");
			cout << "Recursive Factorial Calculation\n";
			cout << "-------------------------------\n";
			break;
		}
		default:
			break;
		}

		cout << numberToFactorialise << "! Has Been Calculated - Please See 'C:/Factorial/Factorial - " + to_string(numberToFactorialise) + ".txt'\n";
		cout << "Factorial Calculation Took " << ((clock() - clockStart) / (double)CLOCKS_PER_SEC) << " Seconds\n";
		cout << "Press Enter to Restart...";
		_getch();
	}
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
		overflow_size = multiply(x, overflow, overflow_size, n);
	}

	//Print the results of the loop
	outputToFile(overflow_size, overflow, n);
}

void outputToFile(int size, long numberToOutput[], long n) {
	//Create output information
	ofstream outputFile;
	outputFile.open("C:\\Factorial\\Factorial - " + to_string(n) + ".txt");

	//Print the results of the loop
	for (long i = size - 1; i >= 0; i--) {
		outputFile << numberToOutput[i];
	}

	outputFile.close();
}

// Takes res[] as input (representation/number of digits) and multiplies it by the long x
unsigned long long multiply(long x, long res[], long res_size, long n)
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

	//cout << ((x % (n/100)) == 0 ? "\rPercentage Complete (Iterative " + to_string(n) + "!): " + to_string((int)(((double)x / (double)n) * 100.0)) + "%":"");
	cout << "\rPercentage Complete (Iterative " + to_string(n) + "!): " + to_string((((double)x / (double)n) * 100.0)) + "%";

	return res_size;
}

void recursiveFactorial(long n)
{
	//Instantiate the array which will hold overflows of the main factorial number
	long overflow[max];
	overflow[0] = 1;

	//Recursively calculate and print
	outputToFile(recursiveMultiply(1, overflow, 1, n), overflow, n);
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

	cout << ((x % (n / 100)) == 0 ? "\rPercentage Complete (Recursive " + to_string(n) + "!): " + to_string((int)(((double)x / (double)n) * 100.0)) + "%" : "");

	return (x == n) ? res_size : recursiveMultiply((x+1), res, res_size, n);
}
