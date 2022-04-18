#pragma once
#include <iostream>
//implement class to store Int data with principle RAII 
//Aplicable Rule 5, implement: constructor,destructor, copyconstructor, move constructor, move assaigment

struct InvalidIndexValue :public std::exception {
	int id;
	InvalidIndexValue(int id) :id(id) {};
	std::string what() {
		std::ostringstream os;
		os << "Invalid Index Value = [" << id << "]\n";
		return os.str();
	}
};

struct InvalidSize :public std::exception {
	int id;
	InvalidSize(int id) :id(id) {};
	std::string what() {
		return "Invalid Size Value =" + id;
	}
};

template<typename storedDataType, int maxSize>
class FixArray {
private:
	storedDataType* arr;
public:
	//Constructor
	FixArray() {
		if (maxSize <= 0) {
			throw InvalidSize(maxSize);
		}
		arr = new storedDataType[maxSize];
		memset(arr, 0, maxSize * sizeof(storedDataType));
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
	int* getArray() {
		return this->arr;
	}
	int getSize() {
		return maxSize;
	}

	storedDataType& operator[](int i) const {
		if (ifIndexIsValid(i)) {
			throw InvalidIndexValue(i);
		}
		return arr[i];
	}
	void print(std::ostringstream& os, int to = maxSize) {
		os << "[ ";
		for (size_t i = 0; i < to; i++) {
			os << arr[i] << ' ';
		}
		os << ']';
	}

	friend std::ostream& operator<<(std::ostream& os, const FixArray<storedDataType, maxSize>& obj) {
		os << "[ ";
		for (size_t i = 0; i < maxSize; i++) {
			os << obj.arr[i] << " ";
		}
		os << "]";
		return os;
	}
};

