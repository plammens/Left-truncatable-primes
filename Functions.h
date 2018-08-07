#pragma once
#include <cmath>
#include <vector>
#include "TruncatedPrime.h"

class TruncatedPrime;

bool IsPrime(int n) {
	int cap = floor(sqrt(n));

	for (int i = 2; i <= cap; i++) {
		if (n%i == 0) return false;
	}

	return true;
}


void printAsList(vector<TruncatedPrime> vec) {

	int lastIndex = vec.size() - 1;
	stringstream list;

	list << "{";

	for (int i = 0; i <= lastIndex; i++) {
		list << vec[i].getValue();

		if (i != lastIndex) list << ", ";
	}

	list << "}";

	cout << list.str() << endl;
}

void printAsList(vector<int> vec) {
	
	int lastIndex = vec.size() - 1;
	stringstream list;

	list << "{";

	for (int i = 0; i <= lastIndex; i++) {
		list << vec[i];

		if (i != lastIndex) list << ", ";
	}

	list << "}";

	cout << list.str() << endl;
}