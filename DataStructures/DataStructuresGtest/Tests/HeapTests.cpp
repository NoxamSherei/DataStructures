#pragma once
#include "../pch.h"
#include "../../DataStructures/inc/Heap.h"

class HeapFixture :public ::testing::Test {
protected:
	int sizeOfTestTable = 15;
	int* testTable = new int[15]{ 40, 20, 10, 50, 100, 110, 120, 90, 80, 150, 130, 140, 30, 60, 70 };
	VectorHeap* minHeap;
	VectorHeap* maxHeap;

public:
	void SetUp() {
		minHeap = new VectorHeap(VectorHeap::heapVersion::MinHeap);
		maxHeap = new VectorHeap(VectorHeap::heapVersion::MaxHeap);
		EXPECT_EQ(minHeap->getVersion(), VectorHeap::heapVersion::MinHeap);
		EXPECT_EQ(maxHeap->getVersion(), VectorHeap::heapVersion::MaxHeap);
	}
	void FillHeap() {
		for (size_t i = 0; i < sizeOfTestTable; i++) {
			minHeap->addElement(testTable[i]);
			maxHeap->addElement(testTable[i]);
		}
	}
};

TEST_F(HeapFixture, sizeHeap) {
	ASSERT_EQ(minHeap->size(), 0);
	ASSERT_EQ(maxHeap->size(), 0);
	minHeap->addElement(1);
	maxHeap->addElement(1);
	ASSERT_EQ(minHeap->size(), 1);
	ASSERT_EQ(maxHeap->size(), 1);
}

TEST_F(HeapFixture, FindRemoveTakeFromHeap) {
	FillHeap();

	EXPECT_EQ(minHeap->findElement(45), false);
	EXPECT_EQ(minHeap->findElement(45), false);
	EXPECT_EQ(minHeap->findElement(40), true);
	EXPECT_EQ(minHeap->findElement(40), true);
	EXPECT_EQ(minHeap->findElement(50), true);
	EXPECT_EQ(maxHeap->findElement(50), true);
	EXPECT_EQ(minHeap->getIdElement(45), -1);
	EXPECT_NE(minHeap->getIdElement(50), NULL);
	EXPECT_EQ(maxHeap->getIdElement(45), -1);
	ASSERT_NE(maxHeap->getIdElement(50), NULL);
	EXPECT_EQ(minHeap->size(), sizeOfTestTable);
	EXPECT_EQ(maxHeap->size(), sizeOfTestTable);
	//Not existing Data to Take
	EXPECT_EQ(minHeap->takeElementWithId(minHeap->getIdElement(45)), -1);
	EXPECT_EQ(maxHeap->takeElementWithId(maxHeap->getIdElement(45)), -1);
	EXPECT_EQ(minHeap->size(), sizeOfTestTable);
	ASSERT_EQ(maxHeap->size(), sizeOfTestTable);
	//ExistingDataToTake
	EXPECT_EQ(minHeap->takeElementWithId(minHeap->getIdElement(50)), 50);
	EXPECT_EQ(maxHeap->takeElementWithId(maxHeap->getIdElement(50)), 50);
	EXPECT_EQ(minHeap->findElement(50), false);
	EXPECT_EQ(maxHeap->findElement(50), false);
	EXPECT_EQ(minHeap->size(), sizeOfTestTable-1);
	ASSERT_EQ(maxHeap->size(), sizeOfTestTable-1);
	//Not existing Data to Remove
	minHeap->removeElementWithId(minHeap->getIdElement(45));
	maxHeap->removeElementWithId(maxHeap->getIdElement(45));
	EXPECT_EQ(minHeap->size(), sizeOfTestTable-1);
	ASSERT_EQ(maxHeap->size(), sizeOfTestTable-1);
	//existing Data to Remove
	minHeap->removeElementWithId(minHeap->getIdElement(40));
	maxHeap->removeElementWithId(maxHeap->getIdElement(40));
	EXPECT_EQ(minHeap->size(), sizeOfTestTable-2);
	ASSERT_EQ(maxHeap->size(), sizeOfTestTable-2);
}

TEST_F(HeapFixture, PeekAndTakeTopHeap) {
	FillHeap();

	EXPECT_EQ(minHeap->size(), sizeOfTestTable);
	EXPECT_EQ(maxHeap->size(), sizeOfTestTable);
	EXPECT_EQ(minHeap->peekTop(), 10);
	ASSERT_EQ(maxHeap->peekTop(), 150);
	
	EXPECT_EQ(minHeap->size(), sizeOfTestTable);
	EXPECT_EQ(maxHeap->size(), sizeOfTestTable);
	EXPECT_EQ(minHeap->takeTop(), 10);
	ASSERT_EQ(maxHeap->takeTop(), 150);

	EXPECT_EQ(minHeap->size(), sizeOfTestTable-1);
	EXPECT_EQ(maxHeap->size(), sizeOfTestTable-1);
	EXPECT_EQ(minHeap->peekTop(), 20);
	ASSERT_EQ(maxHeap->peekTop(), 140);
}

TEST_F(HeapFixture, FillHeap) {
	std::string minExpected = "[ ver=0| 10 40 20 50 100 30 60 90 80 150 130 140 110 120 70 ]\n";
	std::string maxExpected = "[ ver=1| 150 130 140 80 120 110 100 20 50 40 90 10 30 60 70 ]\n";
	std::string minTreeExpected = "[ ver=0|\n|-10 {id=0}\n||-40 {id=1}\n|||-50 {id=3}\n||||-90 {id=7}\n||||-80 {id=8}\n|||-100 {id=4}\n||||-150 {id=9}\n||||-130 {id=10}\n||-20 {id=2}\n|||-30 {id=5}\n||||-140 {id=11}\n||||-110 {id=12}\n|||-60 {id=6}\n||||-120 {id=13}\n||||-70 {id=14}\n";
	std::string maxTreeExpected = "[ ver=1|\n|-150 {id=0}\n||-130 {id=1}\n|||-80 {id=3}\n||||-20 {id=7}\n||||-50 {id=8}\n|||-120 {id=4}\n||||-40 {id=9}\n||||-90 {id=10}\n||-140 {id=2}\n|||-110 {id=5}\n||||-10 {id=11}\n||||-30 {id=12}\n|||-100 {id=6}\n||||-60 {id=13}\n||||-70 {id=14}\n";

	FillHeap();

	testing::internal::CaptureStdout();
	std::cout << *minHeap << std::endl;
	std::string minOutput = testing::internal::GetCapturedStdout();
	std::ostringstream os1;
	minHeap->print(os1, true);
	EXPECT_THAT(minOutput, minExpected);
	EXPECT_THAT(os1.str(), minTreeExpected);

	testing::internal::CaptureStdout();
	std::cout << *maxHeap << std::endl;
	std::string maxOutput = testing::internal::GetCapturedStdout();
	std::ostringstream os2;
	maxHeap->print(os2, true);
	EXPECT_THAT(maxOutput, maxExpected);
	EXPECT_THAT(os2.str(), maxTreeExpected);
}

TEST_F(HeapFixture, SwichHeap) {
	std::string minExpected = "[ ver=0| 10 20 30 50 80 40 100 90 60 130 120 150 70 140 110 ]\n";
	std::string maxExpected = "[ ver=1| 150 140 130 90 100 120 60 70 50 40 80 10 110 20 30 ]\n";
	std::string minTreeExpected = "[ ver=0|\n|-10 {id=0}\n||-20 {id=1}\n|||-50 {id=3}\n||||-90 {id=7}\n||||-60 {id=8}\n|||-80 {id=4}\n||||-130 {id=9}\n||||-120 {id=10}\n||-30 {id=2}\n|||-40 {id=5}\n||||-150 {id=11}\n||||-70 {id=12}\n|||-100 {id=6}\n||||-140 {id=13}\n||||-110 {id=14}\n";
	std::string maxTreeExpected = "[ ver=1|\n|-150 {id=0}\n||-140 {id=1}\n|||-90 {id=3}\n||||-70 {id=7}\n||||-50 {id=8}\n|||-100 {id=4}\n||||-40 {id=9}\n||||-80 {id=10}\n||-130 {id=2}\n|||-120 {id=5}\n||||-10 {id=11}\n||||-110 {id=12}\n|||-60 {id=6}\n||||-20 {id=13}\n||||-30 {id=14}\n";

	FillHeap();

	minHeap->changeVersion(VectorHeap::heapVersion::MaxHeap);
	maxHeap->changeVersion(VectorHeap::heapVersion::MinHeap);
	EXPECT_EQ(minHeap->getVersion(), VectorHeap::heapVersion::MaxHeap);
	EXPECT_EQ(maxHeap->getVersion(), VectorHeap::heapVersion::MinHeap);
	testing::internal::CaptureStdout();
	std::cout << *minHeap << std::endl;
	std::string minOutput = testing::internal::GetCapturedStdout();
	std::ostringstream os1;
	minHeap->print(os1, true);
	EXPECT_THAT(minOutput, maxExpected);
	EXPECT_THAT(os1.str(), maxTreeExpected);

	testing::internal::CaptureStdout();
	std::cout << *maxHeap << std::endl;
	std::string maxOutput = testing::internal::GetCapturedStdout();
	std::ostringstream os2;
	maxHeap->print(os2, true);
	EXPECT_THAT(maxOutput, minExpected);
	EXPECT_THAT(os2.str(), minTreeExpected);
}