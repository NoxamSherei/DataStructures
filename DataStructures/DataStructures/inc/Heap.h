#pragma once
#include <vector>

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

	const bool isEmpty() const { return heapStore.size() == 0; }
	const int32_t getRightElementIndex(const uint32_t errorSize) const { return errorSize * 2 + 1; }
	const int32_t getLeftElementIndex(const uint32_t errorSize) const { return errorSize * 2 + 2; }
	const int32_t getUpperElementIndex(const uint32_t errorSize) const { return std::round((errorSize - 1.5) / 2); }
	const int32_t getLastElementIndex() const { return heapStore.size() - 1; }
	bool checkIfIsSmaller(const uint32_t id1, const uint32_t id2) const { return heapStore[id1] < heapStore[id2]; }
	bool checkIfIsLarger(const uint32_t id1, const uint32_t id2) const { return heapStore[id1] > heapStore[id2]; }
	void swap(const uint32_t id1, const uint32_t id2) {
		auto temp = heapStore[id1];
		heapStore[id1] = heapStore[id2];
		heapStore[id2] = temp;
	}
	void putOnTheCorrectSpot(const int32_t currentId) {
		int32_t checkedId = getUpperElementIndex(currentId);
		if (currentId != 0) {
			if (version == heapVersion::MinHeap ? checkIfIsSmaller(currentId, checkedId) : checkIfIsLarger(currentId, checkedId)) {
				swap(currentId, checkedId);
				putOnTheCorrectSpot(checkedId);
			}
		}
		checkedId = getRightElementIndex(currentId);
		if (checkedId < size()) {
			if (version == heapVersion::MinHeap ? checkIfIsLarger(currentId, checkedId) : checkIfIsSmaller(currentId, checkedId)) {
				swap(currentId, checkedId);
				putOnTheCorrectSpot(checkedId);
			}
		}
		checkedId = getLeftElementIndex(currentId);
		if (checkedId < size()) {
			if (version == heapVersion::MinHeap ? checkIfIsLarger(currentId, checkedId) : checkIfIsSmaller(currentId, checkedId)) {
				swap(currentId, checkedId);
				putOnTheCorrectSpot(checkedId);
			}
		}
	}
	void printAsTree(std::ostringstream& os, int32_t errorSize, int level = 0) {
		for (size_t i = 0; i < level + 1; i++) {
			os << "|";
		}
		os << "-";
		os << heapStore[errorSize] << " {id=" << errorSize << "}\n";
		int32_t nextId = getRightElementIndex(errorSize);
		if (nextId < size()) {
			printAsTree(os, nextId, 1 + level);
		}
		nextId = getLeftElementIndex(errorSize);
		if (nextId < size()) {
			printAsTree(os, nextId, 1 + level);
		}
	}

	bool checkIfIndexIsInRagne(int index) {
		if (index < size() && index >= 0) {
			return true;
		}
		else {
			return false;
		}
	}
public:
	VectorHeap(heapVersion version) :version(version) {}
	virtual ~VectorHeap() {};
	VectorHeap(VectorHeap& otherHeap) {
		this->heapStore = otherHeap.heapStore;
		this->version = otherHeap.version;
	}
	heapVersion getVersion() {
		return version;
	}
	void changeVersion(heapVersion newVersion) {
		version = newVersion;
		for (size_t i = getLastElementIndex(); i > 0; i--) {
			putOnTheCorrectSpot(i);
		}
	}
	const uint32_t size() const { return heapStore.size(); }
	void addElement(const int32_t element) {
		heapStore.push_back(element);
		if (size() > 1) {
			putOnTheCorrectSpot(getLastElementIndex());
		}
	}
	int32_t peekTop()const {
		return heapStore[0];
	}

	int32_t takeTop() {
		int32_t toReturn = heapStore[0];
		removeElementWithId(0);
		return toReturn;
	}

	int32_t takeElementWithId(const int32_t toTake) {
		if (toTake < size() && toTake >= 0) {
			int32_t toReturn = heapStore[toTake];
			swap(toTake, getLastElementIndex());
			heapStore.pop_back();
			putOnTheCorrectSpot(toTake);
			return toReturn;
		}
		return notFound;
	}

	void removeElementWithId(const int32_t indexOfElement) {
		if (checkIfIndexIsInRagne(indexOfElement)) {
			swap(indexOfElement, getLastElementIndex());
			heapStore.pop_back();
			putOnTheCorrectSpot(indexOfElement);
		}
	}

	void removeElementWithValue(const int32_t valueOfElement) {
		auto indexOfElement = getIdElement(valueOfElement);
		if (indexOfElement != notFound) {
			removeElementWithId(indexOfElement);
		}
	}

	bool findElement(const int32_t searched)const {
		for (size_t i = 0; i < size(); i++) {
			if (searched == heapStore[i])return true;
		}
		return false;
	}

	int32_t getIdElement(int32_t searched) const {
		for (size_t i = 0; i < size(); i++) {
			if (searched == heapStore[i])return i;
		}
		return notFound;
	}

	void print(std::ostringstream& os, bool asTree = false) {
		if (asTree) {
			os << "[ ver=" << version << "|\n";
			printAsTree(os, 0);
		}
		else {
			os << *this;
		}
	}

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