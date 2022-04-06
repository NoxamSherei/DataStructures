#pragma once
#include <iostream>
//implement class to store Int data with principle RAII 
//Aplicable Rule 5, implement: constructor,destructor, copyconstructor, move constructor, move assaigment
template<typename storedDataType>
class FixedArray {
private:
	storedDataType* arr;
	int size;
public:
	//Constructor
	FixedArray(unsigned int size) {
		try {
			if (size > 0) {
				arr = new storedDataType[size];
				memset(arr, 0, size * sizeof(storedDataType));
				this->size = size;
			}
			else {
				throw size;
			}
		}
		catch (int e) {
			std::cerr << "Size can't be " << e << '\n';
		}
	}
	//Copy Constructor
	FixedArray(const FixedArray& intArr) :arr(new storedDataType[intArr.size]), size(intArr.size) {
		std::cout << "copy constr\n";
		memcpy(arr, intArr.arr, size * sizeof(storedDataType));
	}
	//Move Construcor
	FixedArray(FixedArray&& intArr) :arr(intArr.arr), size(intArr.size) {
		std::cout << "move constr\n";
		intArr.arr = nullptr;
	}
	//Move Assaigment
	FixedArray& operator=(FixedArray&& other) {
		if (other.size == size) {
			arr = other.arr;
			size = other.size;
			other.arr = nullptr;
		}
		else if (other.size > size) {
			memcpy(arr, other.arr, size * sizeof(storedDataType));
			other.arr = nullptr;
		}
		else {
			memcpy(arr, other.arr, other.size * sizeof(storedDataType));
			other.arr = nullptr;
		}
		std::cout << "move assaigment\n";
		return *this;
	}
	//Destructor
	~FixedArray() {
		delete[] arr;
	}

	storedDataType& operator[](int i) const {
		if (i < 0 or i >= size) {
			std::cerr << i << " is OutOfRange\n";
			exit(0);
		}
		return arr[i];
	}
};