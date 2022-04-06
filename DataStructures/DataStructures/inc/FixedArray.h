#pragma once
#include <iostream>
//implement class to store Int data with principle RAII 
//Aplicable Rule 5, implement: constructor,destructor, copyconstructor, move constructor, move assaigment
template<typename storedDataType, int maxSize>
class FixedArray {
private:
	storedDataType* arr;
public:
	//Constructor
	FixedArray() {
		try {
			if (maxSize > 0) {
				arr = new storedDataType[maxSize];
				memset(arr, 0, maxSize * sizeof(storedDataType));
			}
			else {
				throw maxSize;
			}
		}
		catch (int e) {
			std::cerr << "Size can't be " << e << '\n';
		}
	}
	//Copy Constructor
	FixedArray(const FixedArray& intArr) :arr(new storedDataType[maxSize]) {
		std::cout << "copy constr\n";
		memcpy(arr, intArr.arr, maxSize * sizeof(storedDataType));
	}
	//Move Construcor
	FixedArray(FixedArray&& intArr) :arr(intArr.arr) {
		std::cout << "move constr\n";
		intArr.arr = nullptr;
	}
	//Move Assaigment
	FixedArray& operator=(FixedArray&& other) {
		arr = other.arr;
		other.arr = nullptr;
		std::cout << "move assaigment\n";
		return *this;
	}
	//Destructor
	~FixedArray() {
		delete[] arr;
	}
	storedDataType& operator[](int i) const {
		if (i < 0 or i >= maxSize) {
			std::cerr << i << " is OutOfRange\n";
			exit(0);
		}
		return arr[i];
	}
	void print(std::ostringstream& os,int to=maxSize) {
		for (size_t i = 0; i < to; i++) {
			os<<'['<<arr[i] << ']';
		}
		os << '\n';
	}
};