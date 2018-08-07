#pragma once
#include "stdafx.h"
#include <vector>
#include <sstream>


template <typename T> bool IsPrime(T n) {
	unsigned long long cap = floor(sqrt(n));

	for (int i = 2; i <= cap; i++) {
		if (n%i == 0) return false;
	}

	return true;
}

class TruncatedPrime {
private:
	unsigned long long int value;
	vector<TruncatedPrime> parents;

public:
	TruncatedPrime(unsigned long long n=7): value(n){}

	unsigned long long getValue() {
		return value;
	}

	vector<TruncatedPrime> getParents() {
		if (parents.size() == 0) this->findParents();
		return parents;
	}

	void findParents() {
		for (int i = 1; i <= 9; i++) {
			stringstream concat;
			unsigned long long int candidate;

			concat << i << value;
			concat >> candidate;


			if (IsPrime(candidate)) {
				TruncatedPrime parent(candidate); //Create new candidate TruncatedPrime object
				parents.push_back(parent);
			} 
		}
	}

};