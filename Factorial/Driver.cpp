#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

#define max 300000000

#pragma region HelperClass

class Helper {
	public: 
		bool Helper::outputToFile(int size, long numberToOutput[], long n);
		bool Helper::protectFactoriseInputError();
		bool Helper::protectMenuInputError();
		bool Helper::printStartMenu();
};

bool Helper::printStartMenu() {
	system("cls");
	std::cout << "BSc Computing and Internet Technologies - Advanced Programming A2 - Benjamin Pople" << endl << endl;
	std::cout << "1. Iterative" << endl;
	std::cout << "2. Recursive" << endl;
	std::cout << "Please Select a Factorial Calculation Method (1/2): ";
	return true;
}

//If error is detected on n input
bool Helper::protectFactoriseInputError() {
	//Reset error code
	cin.clear();
	//Clear cin buffer
	cin.ignore(max, '\n');
	//Error message and restart
	std::cout << "Incorrect or Negative Number Entered\n";
	std::cout << "Press Enter to Restart...";
	_getch();
	return true;
}

//If error is detected on menu input
bool Helper::protectMenuInputError() {
	//Reset error code
	cin.clear();
	//Clear cin buffer
	cin.ignore(max, '\n');
	//Show error message
	system("cls");
	std::cout << "Incorrect Menu Entry, Press Enter to Try Again...";
	_getch();
	return true;
}

bool Helper::outputToFile(int size, long numberToOutput[], long n) {
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
		return true;
	}
	else {
		//Show error message
		system("cls");
		std::cout << "Invalid Output Detected - Press Enter to Restart\n";
		_getch();
		outputFile.close();
		return false;
	}
}

#pragma endregion

#pragma region FactorialClass
class Factorial {

public:
	void Factorial::factorise(long n);
	unsigned long long Factorial::multiply(long iterator, long tempOverflowArr[], long tempOverflowArrSize, long n);
	bool Factorial::outputToFile(int size, long numberToOutput[], long n);
};


void Factorial::factorise(long n)
{
	long long_overflow[max];
	//Instantiate the array which will hold overflows of the main factorial number
	long_overflow[0] = 1;
	unsigned long longOverflowSize = 1;

	//Iterative factorial approach (calls function multiply however is still loop-based)
	for (long x = 1; x <= n; x++) {
		longOverflowSize = Factorial::multiply(x, long_overflow, longOverflowSize, n);
	}

	//Print the results of the loop
	Helper helper;
	helper.outputToFile(longOverflowSize, long_overflow, n);
}

//Takes res[] as input (representation/number of digits) and multiplies it by the long x
unsigned long long Factorial::multiply(long iterator, long tempOverflowArr[], long tempOverflowArrSize, long n)
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

	std::cout << ((iterator % ((n+100) / 100)) == 0 ? "\rPercentage Complete (Iterative " + to_string(n) + "!): " + to_string((int)(((double)iterator / (double)n) * 100.0)) + "%" : "");
	
	//std::cout << "\rPercentage Complete (Iterative " + to_string(n) + "!): " + to_string((((double)iterator / (double)n) * 100.0)) + "%";
	//system(("TITLE " + to_string((((double)iterator / (double)n) * 100.0)) + "%").c_str());

	return tempOverflowArrSize;
}

bool Factorial::outputToFile(int size, long numberToOutput[], long n) {
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
		return true;
	}
	else {
		//Show error message
		system("cls");
		std::cout << "Invalid Output Detected - Press Enter to Restart\n";
		_getch();
		outputFile.close();
		return false;
	}
}
#pragma endregion

#pragma region RecursiveFactorialClass

class RecursiveFactorial {
	public:
		void RecursiveFactorial::recursiveFactorial(long n);
		unsigned long long RecursiveFactorial::recursiveMultiply(long iterator, long tempOverflowArr[], long tempOverflowArrSize, long n);
};

void RecursiveFactorial::recursiveFactorial(long n)
{
	Helper helper;
	//Instantiate the array which will hold overflows of the main factorial number
	long longOverflow[max];
	longOverflow[0] = 1;

	//Recursively calculate and print
	helper.outputToFile(recursiveMultiply(1, longOverflow, 1, n), longOverflow, n);
}

//Takes res[] as input (representation/number of digits) and multiplies it by the long x
unsigned long long RecursiveFactorial::recursiveMultiply(long iterator, long tempOverflowArr[], long tempOverflowArrSize, long n)
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

	std::cout << ((iterator % (n / 100)) == 0 ? "\rPercentage Complete (Recursive " + to_string(n) + "!): " + to_string((int)(((double)iterator / (double)n) * 100.0)) + "%" : "");

	return (iterator == n) ? tempOverflowArrSize : recursiveMultiply((iterator + 1), tempOverflowArr, tempOverflowArrSize, n);
}

#pragma endregion

int main() {
	int selectedMethod;
	long numberToFactorialise;
	clock_t clockStart;
	Helper helper;

	system("TITLE Ben Pople - Factorial Calculator - BSc (Hons) Computing and Internet Technologies");

	while (true)
	{
		helper.printStartMenu();
		cin >> selectedMethod;

		/* If we get incorrect user input, such as a string, cin throws an error that will case infinite loop */
		if (cin.fail()) 
			if (helper.protectMenuInputError()) 
				main();

		system("cls");

		switch (selectedMethod)
		{
		case(1): {
			//Iterative
			std::cout << "Please Enter n!: ";
			cin >> numberToFactorialise;
			if (!cin.fail())
			{
				//If negative number has been entered 
				if (numberToFactorialise < 0) 
					if (helper.protectFactoriseInputError())
						main();

				//Start clock, calculate factorial and begin output
				system("cls");
				clockStart = clock();

				Factorial factorial;
				factorial.Factorial::factorise(numberToFactorialise);

				system("cls");
				std::cout << "Iterative Factorial Calculation\n";
				std::cout << "-------------------------------\n";
			} else {
				if (helper.protectFactoriseInputError()) main();
			}
			break;
		}
		case(2): {
			//Recursive
			std::cout << "Please Enter n!: ";
			cin >> numberToFactorialise;
			if (!cin.fail())
			{
				//If negative number has been entered 
				if (numberToFactorialise < 0) if(helper.protectFactoriseInputError()) main();

				//Start clock, calculate factorial and begin output
				system("cls");
				clockStart = clock();
				RecursiveFactorial recursiveFactorial;
				recursiveFactorial.recursiveFactorial(numberToFactorialise);
				system("cls");
				std::cout << "Recursive Factorial Calculation\n";
				std::cout << "-------------------------------\n";
			} else {
				if(helper.protectFactoriseInputError()) main();
			}
			break;
		}
		default:
			main();
			break;
		}

		std::cout << numberToFactorialise << "! Has Been Calculated - Please See 'C:/Factorial/Factorial - " + to_string(numberToFactorialise) + ".txt'\n";
		std::cout << "Factorial Calculation Took " << ((clock() - clockStart) / (double)CLOCKS_PER_SEC) << " Seconds\n";
		std::cout << "Press Enter to Restart...";
		_getch();
	}
	return 0;
}

