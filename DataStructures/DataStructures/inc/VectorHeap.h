#pragma once
#include <vector>
#include <sstream>

using std::vector;

#define notFound -1

class VectorHeap {
public:
	enum heapVersion {
		MinHeap,
		MaxHeap
	};
private:
	vector<int32_t> heapStore;
	heapVersion version;

	const bool isEmpty() const;
	const int32_t getRightElementIndex(const uint32_t errorSize) const;
	const int32_t getLeftElementIndex(const uint32_t errorSize) const;
	const int32_t getUpperElementIndex(const uint32_t errorSize) const;
	const int32_t getLastElementIndex() const;
	bool checkIfIsSmaller(const uint32_t id1, const uint32_t id2) const;
	bool checkIfIsLarger(const uint32_t id1, const uint32_t id2) const;
	void swap(const uint32_t id1, const uint32_t id2);
	void putOnTheCorrectSpot(const int32_t currentId);
	void printAsTree(std::ostringstream& os, int32_t errorSize, int level = 0);
	bool checkIfIndexIsInRagne(int index);
public:
	VectorHeap(heapVersion version);
	virtual ~VectorHeap();
	VectorHeap(VectorHeap& otherHeap);
	heapVersion getVersion();
	void changeVersion(heapVersion newVersion);
	const uint32_t size() const;
	void addElement(const int32_t element);
	int32_t peekTop()const;
	int32_t takeTop();
	int32_t takeElementWithId(const int32_t toTake);
	void removeElementWithId(const int32_t indexOfElement);
	void removeElementWithValue(const int32_t valueOfElement);
	bool findElement(const int32_t searched)const;
	int32_t getIdElement(int32_t searched) const;
	void print(std::ostringstream& os, bool asTree = false);

	friend std::ostream& operator<<(std::ostream& os, const VectorHeap& obj) {
		os << "[ ver=";
		os << obj.version << "| ";
		for (size_t i = 0; i < obj.size(); i++) {
			os << obj.heapStore[i] << " ";
		}
		os << "]";
		return os;
	}
};