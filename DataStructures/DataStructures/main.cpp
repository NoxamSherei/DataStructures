#include <iostream>
//dataStructures
#include "inc/HashTableWithCaining.h"
#include "inc/Stack.h"
#include "inc/FixedArray.h"
#include "inc/Queue.h"
#include "main.h"
#include "inc/Heap.h"

int main() {
	VectorHeap minHeap(heapVersion::MinHeap);
	VectorHeap maxHeap(heapVersion::MaxHeap);
	int testTable[15]{ 42,69,102,402,5,2,9,10,30,70,10,25,64,239,234 };
	for (size_t i = 0; i < 15; i++) {
		minHeap.addElement(testTable[i]);
		maxHeap.addElement(testTable[i]);
	}
	{
		std::ostringstream os;
		minHeap.print(os);
		std::cout << os.str();
	}
	{
		std::ostringstream os;
		maxHeap.print(os);
		std::cout << os.str();
	}
	minHeap.changeVersion(heapVersion::MaxHeap);
	std::cout << "change Version to max = ";
	{
		std::ostringstream os;
		minHeap.print(os);
		std::cout << os.str();
	}

	Queue<4> queue;
	queue.enqueue(1);
	queue.enqueue(3);
	queue.enqueue(4);
	queue.enqueue(5);
	{
		std::ostringstream os;
		queue.print(os);
		std::cout << os.str();
	}
	printf("Peek=%d\n", queue.peek());
	printf("Dequeue=%d\n", queue.dequeue());
	printf("Peek=%d\n", queue.peek());
	{
		std::ostringstream os;
		queue.print(os);
		std::cout << os.str();
	}

	FixedArray<int, 10> arr1;
	for (size_t i = 0; i < 10; i++) {
		arr1[i] = i;
	}
	{
		std::ostringstream os;
		arr1.print(os);
		std::cout << os.str();
	}

	HashTableWithChaining<int, 5> hashTable;
	for (size_t i = 0; i < 25; i = i + 2) {
		hashTable.addElement(i);
	}
	printf("noOfElements: %d, 5=%d, 6=%d\n", hashTable.getNoOfElements(), hashTable.checkElement(5), hashTable.checkElement(6));
	printf("remove element 5=%d\n", hashTable.removeElement(5));
	printf("remove element 6=%d\n", hashTable.removeElement(6));
	printf("noOfElements: %d, 5=%d, 6=%d\n", hashTable.getNoOfElements(), hashTable.checkElement(5), hashTable.checkElement(6));
	{
		std::ostringstream os;
		hashTable.printHashTable(os);
		std::cout << os.str();
	}

	SimpleStack stack(10);
	for (size_t i = 0; i < 11; i++) {
		printf(" insert %d was %d\n", i, stack.insertElement(i));
	}
	{
		std::ostringstream os;
		stack.print(os);
		std::cout << os.str();
	}
	printf(" peek=%d\n", stack.peekElement());
	printf(" take=%d\n", stack.takeElement());
	printf(" peek=%d\n", stack.peekElement());
	printf(" insert %d was %d\n", 42, stack.insertElement(42));
	printf(" peek=%d\n", stack.peekElement());
	printf(" find %d=%d\n", 42, stack.findElement(42));
	printf(" find %d=%d\n", 9, stack.findElement(9));
	printf(" find %d=%d\n", 5, stack.findElement(5));
	return 0;
}