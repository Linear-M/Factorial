#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Helper {

	void Helper::outputToFile(int size, long numberToOutput[], long n) {
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
		}
		else {
			//Show error message
			system("cls");
			cout << "Invalid Output Detected - Press Enter to Restart\n";
			_getch();
			outputFile.close();
			//main();
		}
	}

};