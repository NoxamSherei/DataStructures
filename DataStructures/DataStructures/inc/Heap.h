#pragma once
#include <vector>

using std::vector;

enum heapVersion {
	MinHeap,
	MaxHeap
};
class VectorHeap {
private:
	vector<int32_t> heapStore;
	heapVersion version;

	const bool isEmpty() const { return heapStore.size() == 0; }
	const uint32_t getRightElementIndex(const uint32_t id) const { return id * 2 + 1; }
	const uint32_t getLeftElementIndex(const uint32_t id) const { return id * 2 + 2; }
	const uint32_t getUpperElementIndex(const uint32_t id) const { return std::round(id - 1) / 2; }
	const uint32_t getLastElementIndex() const { return heapStore.size() - 1; }
	bool checkIfIsSmaller(const uint32_t id1, const uint32_t id2) const { return heapStore[id1] < heapStore[id2]; }
	bool checkIfIsLarger(const uint32_t id1, const uint32_t id2) const { return heapStore[id1] > heapStore[id2]; }
	void swap(const uint32_t id1, const uint32_t id2) {
		auto temp = heapStore[id1];
		heapStore[id1] = heapStore[id2];
		heapStore[id2] = temp;
	}
	void putOnTheCorrectSpot(const uint32_t currentId) {
		uint32_t checkedId = getUpperElementIndex(currentId);
		if (currentId != 0) {
			if (version == heapVersion::MinHeap ? checkIfIsSmaller(currentId, checkedId) : checkIfIsLarger(currentId, checkedId)) {
				swap(currentId, checkedId);
				putOnTheCorrectSpot(checkedId);
			}
		}
		checkedId = getRightElementIndex(currentId);
		if (checkedId <= size()) {
			if (version == heapVersion::MinHeap ? checkIfIsLarger(currentId, checkedId) : checkIfIsSmaller(currentId, checkedId)) {
				swap(currentId, checkedId);
				putOnTheCorrectSpot(checkedId);
			}
		}
		checkedId = getLeftElementIndex(currentId);
		if (checkedId <= size()) {
			if (version == heapVersion::MinHeap ? checkIfIsLarger(currentId, checkedId) : checkIfIsSmaller(currentId, checkedId)) {
				swap(currentId, checkedId);
				putOnTheCorrectSpot(checkedId);
			}
		}
	}
public:
	VectorHeap(heapVersion version) :version(version) {}
	virtual ~VectorHeap() {};
	VectorHeap(VectorHeap& otherHeap) {
		this->heapStore = otherHeap.heapStore;
		this->version = otherHeap.version;
	}
	void changeVersion(heapVersion newVersion) {
		version = newVersion;
		putOnTheCorrectSpot(0);
	}
	const uint32_t size() const { return heapStore.size(); }
	void addElement(const int32_t element) {
		heapStore.push_back(element);
		if (size() > 1) {
			putOnTheCorrectSpot(getLastElementIndex());
		}
	}

	void print(std::ostringstream& os) {
		os << " Heap: ";
		for (size_t i = 0; i < size(); i++) {
			os<<'{'<<heapStore[i]<<'}';
		}
		os << '\n';
	}
};