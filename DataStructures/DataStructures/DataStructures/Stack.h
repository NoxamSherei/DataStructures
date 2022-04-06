#pragma once
//SimpleStack with fixed maxSize
//Complexity
//insert O(1)
//peek O(1)
//search O(n)
//take O(1)
//to do: implement rule 5
class SimpleStack
{
private:
	int* storedData;
	unsigned int acctualSize;
	const unsigned int maximalSize;
	bool possibleToInsert() const {
		return maximalSize >= acctualSize + 1;
	}
	bool isEmpty() const {
		return acctualSize == 0;
	}
public:
	SimpleStack(const unsigned int maximalSize) :
		storedData(new int[maximalSize]),
		acctualSize(0),
		maximalSize(maximalSize)
	{}
	~SimpleStack()
	{
		delete[] storedData;
	}
	bool insertElement(int elementToInser)
	{
		if (possibleToInsert())
		{
			storedData[acctualSize++] = elementToInser;
			return true;
		}
		return false;
	}
	int peekElement() const
	{
		return storedData[acctualSize-1];
	}
	int takeElement()
	{
		return storedData[--acctualSize];
	}
	bool findElement(int elementToFind)
	{
		if (elementToFind == peekElement()) return true;
		for (size_t i = 0; i < acctualSize-1; i++)
		{
			if (storedData[i] == elementToFind) return true;
		}
		return false;
	}
	void print(std::ostringstream& os) const
	{
		os << "SimpleStack \\\\ ";
		for (size_t i = 0; i < acctualSize; i++)
		{
			os << '[' << storedData[i] << ']';
		}
		os << '\n';
	}
};