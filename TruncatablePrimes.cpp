// TruncatablePrimes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "TruncatedPrime.h"
#include "Colors.h"


template <typename T> string toListString(vector<T> vec);
string toListString(vector<TruncatedPrime> vec);
template <class T> int numDigits(T number);

//Traversing algorithms
vector<unsigned long long> digitSearch(int nOfDigits); //Breadth-first search of TPs
void climbABranch(); //User decides which way to go

//Const
const int oneDigits[] = { 2,3,5,7 };

//Main
int main()
{
	//cout << toListString(digitSearch(5)) << endl;

	climbABranch();

	cout << endl;
	system("pause"); //Such a badass
    return 0;
}

//Secondary functions
template <typename T> string toListString(vector<T> vec) {

	int lastIndex = vec.size() - 1;
	stringstream list;

	list << "{";

	for (int i = 0; i <= lastIndex; i++) {
		list << vec[i];

		if (i != lastIndex) list << ", ";
	}

	list << "}";

	return list.str();
}

string toListString(vector<TruncatedPrime> vec) {

	int lastIndex = vec.size() - 1;
	stringstream list;

	list << "{";

	for (int i = 0; i <= lastIndex; i++) {
		list << vec[i].getValue();

		if (i != lastIndex) list << ", ";
	}

	list << "}";

	return list.str();
}

template <class T> int numDigits(T number)
{
	int digits = 0;
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}


//Traversing algorithms
vector<unsigned long long> digitSearch(int nOfDigits)
{
	if (nOfDigits <= 0) {
		cout << "Incompatible number of digits!" << endl;
		return vector<unsigned long long>(0);
	}

	vector<vector<TruncatedPrime>> matrixOfTPs(1, vector<TruncatedPrime>(4)); //Create 1 by 4 array to store one-digit TPs

	for (int i = 0; i < 4; i++) {
		TruncatedPrime tp(oneDigits[i]);
		matrixOfTPs[0][i] = tp;
	}

	int count = 4;

	//For every digit requested, expand previous layer
	for (int n = 2; n <= nOfDigits; n++) {


		vector<TruncatedPrime> previous = matrixOfTPs.back(); //Last 'layer' (i.e. TPs with current number of digits)

		vector<TruncatedPrime> current; //Current (empty) layer

										//Expand previous layer
		for (int i = 0; i < previous.size(); i++) {

			previous[i].findParents();
			vector<TruncatedPrime> parents = previous[i].getParents();

			current.insert(current.end(), parents.begin(), parents.end());

			count += parents.size();
			/*if (0 <= count % (176*nOfDigits/100) && count % 426 <= 9 && parents.size() >=10)*/
			system("CLS"); //Thug life
			cout << "Found " << count << " left-truncatable primes" << endl;
		}

		if (current.size() == 0) break;
		matrixOfTPs.push_back(current); //Append vector to matrix for storing TPs of n digits
	}



	//Return result as flattened vector<int>
	vector<unsigned long long> result;


	for (int i = 0; i < matrixOfTPs.size(); i++) {
		for (int j = 0; j < matrixOfTPs[i].size(); j++) {

			result.push_back(matrixOfTPs[i][j].getValue());
		}
	}

	cout << endl;
	
	return result;
}


void climbABranch() {
	vector<int> options(4); //Not 'TruncatedPrimes' for checking input later

	//Initialize options
	for (int i = 0; i < 4; i++) {
		options[i] = oneDigits[i];
	}

	
	vector<int> currentPath; //Path followed up to now
	int digits=1; //Current number of digits

	while (options.size() > 0) {
		
		string input;
		int choice;

		cout << "DIGITS: " << digits;
		cout << endl << "Path followed: " << toListString(currentPath) << endl;
		cout << "Your options are " << toListString(options) << "." << endl;

		//Input checking
		while (true) {
			cout << "Choose one of the options: ";
			getline(cin, input);

			// This code converts from string to number safely.
			stringstream stream(input);

			if (stream >> choice) {

				//Check if is one of the given choices
				if (find(options.begin(), options.end(), choice) != options.end()) {
					break; //Case: correct input

				}
				else {//Not an option
					cout << endl << red << "That's not one of the possible options. Choose again." << white << endl;
				}

			}
			else { //Not a number
				cout << endl << red << "That is not a valid number. Try again." << white << endl;
			}
		}

		//Arrives here if correct input
		currentPath.push_back(choice);

		vector<TruncatedPrime> buffer1 = TruncatedPrime(choice).getParents(); //For converting to vector<int>
		vector<int> buffer2(buffer1.size()); //For converting to vector<int>

		for (int i = 0; i < buffer1.size(); i++) {
			buffer2[i] = buffer1[i].getValue();
		}

		options = buffer2;

		cout << endl;
		++digits;
	}
	
	cout << endl << "Dead end! You got to the number " << currentPath.back() << ", that has " 
		<< digits << " digits, following the path " << toListString(currentPath);
}
