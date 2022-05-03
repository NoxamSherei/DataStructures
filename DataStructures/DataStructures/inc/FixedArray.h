#pragma once
#include <iostream>
#include "errorStructs/ErrorStructs.h"
//implement class to store Int data with principle RAII 
//Aplicable Rule 5, implement: constructor,destructor, copyconstructor, move constructor, move assaigment
template<typename storedDataType, size_t maxSize>
class FixArray {
private:
	storedDataType* arr;
public:
	//Constructor
	FixArray() {
		if (maxSize <= 0) {
			throw ErrorInvalidSize(maxSize);
		}
		arr = new storedDataType[maxSize];
	}
	//Copy Constructor
	FixArray(const FixArray& intArr) :arr(new storedDataType[maxSize]) {
		memcpy(arr, intArr.arr, maxSize * sizeof(storedDataType));
	}
	//Copy Assaigment
	FixArray& operator=(FixArray& other) {
		this->arr = new int[maxSize];
		memcpy(this->arr, other.arr, maxSize * sizeof(storedDataType));
		return *this;
	}
	//Move Construcor
	FixArray(FixArray&& intArr) :arr(intArr.arr) {
		intArr.arr = nullptr;
	}
	//Move Assaigment
	FixArray& operator=(FixArray&& other) {
		arr = other.arr;
		other.arr = nullptr;
		return *this;
	}
	//Destructor
	~FixArray() {
		delete[] arr;
	}
	bool ifIndexIsValid(const int& i) const {
		return i < 0 or i >= maxSize;
	}
	void fill(const storedDataType& data) {
		for (auto it = this->getBegin(); it != this->getEnd(); it++) {
			*it = data;
		}
	}
	size_t getSize() {
		return maxSize;
	}
	storedDataType* getBegin() {
		return &arr[0];
	}
	storedDataType* getEnd() {
		return &arr[maxSize];
	}

	storedDataType& operator[](int i) const {
		if (ifIndexIsValid(i)) {
			throw ErrorInvalidIndexValue(i);
		}
		return arr[i];
	}
	void print(std::ostringstream& os, int from = 0, int to = maxSize) {
		os << "[ ";
		for (size_t i = from; i < to; i++) {
			os << arr[i] << ' ';
		}
		os << ']';
	}
	friend FixArray<storedDataType, maxSize> operator+(FixArray<storedDataType, maxSize> objLeft, FixArray<storedDataType, maxSize>& objRight) {
		for (size_t i = 0; i < maxSize; i++) {
			objLeft[i] = objLeft[i] + objRight[i];
		}
		return objLeft;
	}
	friend FixArray<storedDataType, maxSize> operator-(FixArray<storedDataType, maxSize> objLeft, FixArray<storedDataType, maxSize>& objRight) {
		for (size_t i = 0; i < maxSize; i++) {
			objLeft[i] = objLeft[i] - objRight[i];
		}
		return objLeft;
	}
	friend FixArray<storedDataType, maxSize> operator*(FixArray<storedDataType, maxSize> objLeft, FixArray<storedDataType, maxSize>& objRight) {
		for (size_t i = 0; i < maxSize; i++) {
			objLeft[i] = objLeft[i] * objRight[i];
		}
		return objLeft;
	}
	friend FixArray<storedDataType, maxSize> operator/(FixArray<storedDataType, maxSize> objLeft, FixArray<storedDataType, maxSize>& objRight) {
		for (size_t i = 0; i < maxSize; i++) {
			objLeft[i] = objLeft[i] / objRight[i];
		}
		return objLeft;
	}

	friend std::ostream& operator<<(std::ostream& os, const FixArray<storedDataType, maxSize>& obj) {
		os << "[ ";
		for (size_t i = 0; i < maxSize; i++) {
			os << obj.arr[i] << " ";
		}
		os << "]";
		return os;
	}

	friend std::istream& operator>>(std::istream& input, FixArray<storedDataType, maxSize>& obj) {
		for (size_t i = 0; i < maxSize; i++) {
			std::cout << i << "/" << maxSize << ":=";
			input >> obj[i];
		}
		return input;
	}
};

