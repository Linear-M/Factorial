#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

unsigned long long multiply(long x, long res[], long res_size, long n), recursiveMultiply(long x, long res[], long res_size, long n); 
void factorial(long n), recursiveFactorial(long n), outputToFile(int size, long numberToOutput[], long n), protectFactoriseInputError(), protectMenuInputError();
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

		/* If we get incorrect user input, such as a string, cin throws an error that will case infinite loop */
		if (cin.fail()) protectMenuInputError();

		system("cls");

		switch (selectedMethod)
		{
		case(1): {
			//Iterative
			cout << "Please Enter n!: ";
			cin >> numberToFactorialise;
			if (!cin.fail())
			{
				//If negative number has been entered 
				if (numberToFactorialise < 0) protectFactoriseInputError();

				//Start clock, calculate factorial and begin output
				system("cls");
				clockStart = clock();
				factorial(numberToFactorialise);
				system("cls");
				cout << "Iterative Factorial Calculation\n";
				cout << "-------------------------------\n";
			} else {
				protectFactoriseInputError();
			}
			break;
		}
		case(2): {
			//Recursive
			cout << "Please Enter n!: ";
			cin >> numberToFactorialise;
			if (!cin.fail())
			{
				//If negative number has been entered 
				if (numberToFactorialise < 0) protectFactoriseInputError();

				//Start clock, calculate factorial and begin output
				system("cls");
				clockStart = clock();
				recursiveFactorial(numberToFactorialise);
				system("cls");
				cout << "Recursive Factorial Calculation\n";
				cout << "-------------------------------\n";
			} else {
				protectFactoriseInputError();
			}
			break;
		}
		default:
			main();
			break;
		}

		cout << numberToFactorialise << "! Has Been Calculated - Please See 'C:/Factorial/Factorial - " + to_string(numberToFactorialise) + ".txt'\n";
		cout << "Factorial Calculation Took " << ((clock() - clockStart) / (double)CLOCKS_PER_SEC) << " Seconds\n";
		cout << "Press Enter to Restart...";
		_getch();
	}
	return 0;
}

//If error is detected on n input
void protectFactoriseInputError() {
	//Reset error code
	cin.clear();
	//Clear cin buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//Error message and restart
	cout << "Incorrect or Negative Number Entered\n";
	cout << "Press Enter to Restart...";
	_getch();
	main();
}

//If error is detected on menu input
void protectMenuInputError() {
	//Reset error code
	cin.clear();
	//Clear cin buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//Show error message
	system("cls");
	cout << "Incorrect Menu Entry, Press Enter to Try Again...";
	_getch();
}

void factorial(long n)
{
	long long_overflow[max];
	//Instantiate the array which will hold overflows of the main factorial number
	long_overflow[0] = 1;
	long longOverflowSize = 1;

	//Iterative factorial approach (calls function multiply however is still loop-based)
	for (long x = 1; x <= n; x++){
		longOverflowSize = multiply(x, long_overflow, longOverflowSize, n);
	}

	//Print the results of the loop
	outputToFile(longOverflowSize, long_overflow, n);
}

void outputToFile(int size, long numberToOutput[], long n) {
	//Create output information
	ofstream outputFile;
	outputFile.open("C:\\Factorial\\Factorial - " + to_string(n) + ".txt");

	//Validate output - take first digit of number, if it is > 0, then whole number is > 0
	if (numberToOutput[size - 1] > 0) {
		//Print the results of the loop
		for (long i = size - 1; i >= 0; i--) {
			outputFile << numberToOutput[i];
		}
		outputFile.close();
	} else {
		//Show error message
		system("cls");
		cout << "Invalid Output Detected - Press Enter to Restart\n";
		_getch();
		outputFile.close();
		main();
	}
}

//Takes res[] as input (representation/number of digits) and multiplies it by the long x
unsigned long long multiply(long iterator, long tempOverflowArr[], long tempOverflowArrSize, long n)
{
	/*Starting some GCSE maths*/
	long carry = 0;  

	//For each individual integer multiply by x
	for (long i = 0; i<tempOverflowArrSize; i++)
	{
		long product = tempOverflowArr[i] * iterator + carry;
		/*New last digit*/
		tempOverflowArr[i] = product % 10;
		/*Overflow stored by carry*/
		carry = product / 10;
	}

	/*Move carry to the array and free buffers*/
	while (carry)
	{
		tempOverflowArr[tempOverflowArrSize] = carry % 10;
		carry = carry / 10;
		tempOverflowArrSize++;
	}

	cout << ((iterator % (n/100)) == 0 ? "\rPercentage Complete (Iterative " + to_string(n) + "!): " + to_string((int)(((double)iterator / (double)n) * 100.0)) + "%":"");
	//cout << "\rPercentage Complete (Iterative " + to_string(n) + "!): " + to_string((((double)iterator / (double)n) * 100.0)) + "%";

	return tempOverflowArrSize;
}

void recursiveFactorial(long n)
{
	//Instantiate the array which will hold overflows of the main factorial number
	long longOverflow[max];
	longOverflow[0] = 1;

	//Recursively calculate and print
	outputToFile(recursiveMultiply(1, longOverflow, 1, n), longOverflow, n);
}

//Takes res[] as input (representation/number of digits) and multiplies it by the long x
unsigned long long recursiveMultiply(long iterator, long tempOverflowArr[], long tempOverflowArrSize, long n)
{
	/*Starting some GCSE maths*/
	long carry = 0;

	//For each individual integer multiply by x
	for (long i = 0; i<tempOverflowArrSize; i++)
	{
		long product = tempOverflowArr[i] * iterator + carry;
		/*New last digit*/
		tempOverflowArr[i] = product % 10;
		/*Overflow stored by carry*/
		carry = product / 10;
	}

	/*Move carry to the array and free buffers*/
	while (carry)
	{
		tempOverflowArr[tempOverflowArrSize] = carry % 10;
		carry = carry / 10;
		tempOverflowArrSize++;
	}

	cout << ((iterator % (n / 100)) == 0 ? "\rPercentage Complete (Recursive " + to_string(n) + "!): " + to_string((int)(((double)iterator / (double)n) * 100.0)) + "%" : "");

	return (iterator == n) ? tempOverflowArrSize : recursiveMultiply((iterator+1), tempOverflowArr, tempOverflowArrSize, n);
}
