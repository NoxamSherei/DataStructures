#include <iostream>
//dataStructures
#include "inc/HashTableWithCaining.h"
#include "inc/Stack.h"
#include "inc/FixedArray.h"

int main() {

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