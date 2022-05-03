#pragma once
#include <string>

struct ErrorInvalidIndexValue :public std::exception {
	int errorIndex;
	ErrorInvalidIndexValue(int errorIndex) :errorIndex(errorIndex) {};
	std::string what() {
		return "Invalid Index Value = [" + std::to_string(errorIndex) + "]\n";
	}
};

struct ErrorInvalidSize :public std::exception {
	int errorSize;
	ErrorInvalidSize(int errorSize) :errorSize(errorSize) {};
	std::string what() {
		return "Invalid Size Value = [" + std::to_string(errorSize) + "]\n";
	}
};