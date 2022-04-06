#pragma once
#include <vector>
#include <array>
#include <sstream>

using std::vector;
using std::array;
using std::ostringstream;

//HashTable with chaing complexity
//insert = O(1)
//search = O(1); worst O(n)
//delete = O(1); worst O(n)
//This HashTable Build not support types like string, chars
template<typename dataType, uint32_t sizeOfTable>
class HashTableWithChaining {
private:
	array<vector<dataType>, sizeOfTable> data;
	uint32_t noOfElements = 0;
	const uint32_t hashing(dataType element) const { return (element * 2 + element * element) % sizeOfTable; }
public:
	const uint32_t getNoOfElements() const { return noOfElements; }
	const uint32_t getSizeOfTable() const { return sizeOfTable; }
	void addElement(const dataType elementToInsert) {
		const uint32_t id = hashing(elementToInsert);
		data[id].push_back(elementToInsert);
		noOfElements++;
	}
	bool checkElement(const dataType elementToCheck) const {
		if (getNoOfElements() == 0) return false;
		const uint32_t id = hashing(elementToCheck);
		const uint32_t size = data[id].size();
		if (size > 0) {
			for (auto elementInTheVec : data[id]) {
				if (elementInTheVec == elementToCheck) return true;
			}
		}
		return false;
	}
	bool removeElement(const dataType elementToRemove) {
		if (getNoOfElements() == 0) return false;
		const uint32_t id = hashing(elementToRemove);
		const uint32_t size = data[id].size();
		if (size > 0) {
			for (auto it = data[id].begin(); it != data[id].end(); it++) {
				if (*it == elementToRemove) {
					data[id].erase(it);
					noOfElements--;
					return true;
				}
			}
		}
		return false;
	}
	void printHashTable(std::ostringstream& os) const {
		for (uint32_t i = 0; i < getSizeOfTable(); i++) {
			os << "| " << i << " [";
			for (uint32_t j = 0; j < data[i].size(); j++) {
				os << '[' << data[i][j] << ']';
			}
			os << "]\n";
		}
	}
};