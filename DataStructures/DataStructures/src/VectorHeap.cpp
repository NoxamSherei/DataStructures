#include "../inc/VectorHeap.h"

VectorHeap::VectorHeap(VectorHeap::heapVersion version) :version(version) {}
VectorHeap::~VectorHeap() {};
VectorHeap::VectorHeap(VectorHeap& otherHeap) {
	this->heapStore = otherHeap.heapStore;
	this->version = otherHeap.version;
}

const bool VectorHeap::isEmpty() const
{
	return heapStore.size() == 0;
}

const int32_t VectorHeap::getRightElementIndex(const uint32_t errorSize) const
{
	return errorSize * 2 + 1;
}
const int32_t VectorHeap::getLeftElementIndex(const uint32_t errorSize) const
{
	return errorSize * 2 + 2;
}
const int32_t VectorHeap::getUpperElementIndex(const uint32_t errorSize) const
{
	return std::round((errorSize - 1.5) / 2);
}
const int32_t VectorHeap::getLastElementIndex() const
{
	return heapStore.size() - 1;
}
bool VectorHeap::checkIfIsSmaller(const uint32_t id1, const uint32_t id2) const
{
	return heapStore[id1] < heapStore[id2];
}
bool VectorHeap::checkIfIsLarger(const uint32_t id1, const uint32_t id2) const
{
	return heapStore[id1] > heapStore[id2];
}
void VectorHeap::swap(const uint32_t id1, const uint32_t id2)
{
	auto temp = heapStore[id1];
	heapStore[id1] = heapStore[id2];
	heapStore[id2] = temp;
}
void VectorHeap::putOnTheCorrectSpot(const int32_t currentId)
{
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
void VectorHeap::printAsTree(std::ostringstream& os, int32_t errorSize, int level)
{
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

bool VectorHeap::checkIfIndexIsInRagne(int index)
{
	if (index < size() && index >= 0) {
		return true;
	}
	else {
		return false;
	}
}

VectorHeap::heapVersion VectorHeap::getVersion()
{
	return version;
}
void VectorHeap::changeVersion(VectorHeap::heapVersion newVersion)
{
	version = newVersion;
	for (size_t i = getLastElementIndex(); i > 0; i--) {
		putOnTheCorrectSpot(i);
	}
}
const uint32_t VectorHeap::size() const
{
	return heapStore.size();
}
void VectorHeap::addElement(const int32_t element)
{
	heapStore.push_back(element);
	if (size() > 1) {
		putOnTheCorrectSpot(getLastElementIndex());
	}
}
int32_t VectorHeap::peekTop()const {
	return heapStore[0];
}

int32_t VectorHeap::takeTop() {
	int32_t toReturn = heapStore[0];
	removeElementWithId(0);
	return toReturn;
}


int32_t VectorHeap::takeElementWithId(const int32_t toTake) {
	if (toTake < size() && toTake >= 0) {
		int32_t toReturn = heapStore[toTake];
		swap(toTake, getLastElementIndex());
		heapStore.pop_back();
		putOnTheCorrectSpot(toTake);
		return toReturn;
	}
	return notFound;
}

void VectorHeap::removeElementWithId(const int32_t indexOfElement) {
	if (checkIfIndexIsInRagne(indexOfElement)) {
		swap(indexOfElement, getLastElementIndex());
		heapStore.pop_back();
		putOnTheCorrectSpot(indexOfElement);
	}
}

void VectorHeap::removeElementWithValue(const int32_t valueOfElement) {
	auto indexOfElement = getIdElement(valueOfElement);
	if (indexOfElement != notFound) {
		removeElementWithId(indexOfElement);
	}
}

bool VectorHeap::findElement(const int32_t searched)const {
	for (size_t i = 0; i < size(); i++) {
		if (searched == heapStore[i])return true;
	}
	return false;
}

int32_t VectorHeap::getIdElement(int32_t searched) const {
	for (size_t i = 0; i < size(); i++) {
		if (searched == heapStore[i])return i;
	}
	return notFound;
}

void VectorHeap::print(std::ostringstream& os, bool asTree) {
	if (asTree) {
		os << "[ ver=" << version << "|\n";
		printAsTree(os, 0);
	}
	else {
		os << *this;
	}
}