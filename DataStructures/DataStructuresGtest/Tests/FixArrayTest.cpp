#pragma once
#include "..\pch.h"
#include "..\..\DataStructures\inc\FixedArray.h"
#include <iostream>
class ArrayTestFixture :public ::testing::Test {
public:
};

TEST_F(ArrayTestFixture, testFixedArrayConstructorsAndAssaigment) {
	FixArray<int, 10> source;
	EXPECT_THAT(source.getSize(),10);
	source[2] = 22;
	//CopyConstructor
	FixArray<int, 10> arrayA(source);
	arrayA[1] = 10;
	ASSERT_NE(source.getArray(), arrayA.getArray());
	ASSERT_NE(nullptr, arrayA.getArray());
	EXPECT_EQ(source[1], 0);
	EXPECT_EQ(source[2], 22);
	EXPECT_EQ(arrayA[1], 10);
	EXPECT_EQ(arrayA[2], 22);
	//CopyAssaigment
	FixArray<int, 10> arrayB = source;
	arrayB[1] = 20;
	ASSERT_NE(source.getArray(), arrayB.getArray());
	ASSERT_NE(nullptr, arrayB.getArray());
	EXPECT_EQ(source[1], 0);
	EXPECT_EQ(source[2], 22);
	EXPECT_EQ(arrayB[1], 20);
	EXPECT_EQ(arrayB[2], 22);
	//MoveConstructor
	auto lastPosA = arrayA.getArray();
	FixArray<int, 10> arrayC(std::move(arrayA));
	ASSERT_NE(arrayC.getArray(), arrayA.getArray());
	ASSERT_THAT(arrayA.getArray(), nullptr);
	ASSERT_THAT(arrayC.getArray(), lastPosA);
	//MoveAssaigment
	auto lastPosB = arrayB.getArray();
	FixArray<int, 10> arrayD = std::move(arrayB);
	ASSERT_NE(arrayD.getArray(), arrayB.getArray());
	ASSERT_THAT(arrayB.getArray(), nullptr);
	ASSERT_THAT(arrayD.getArray(), lastPosB);

	EXPECT_EQ(arrayC[1], 10);
	EXPECT_EQ(arrayC[2], 22);
	EXPECT_EQ(arrayD[1], 20);
	EXPECT_EQ(arrayD[2], 22);
}

TEST_F(ArrayTestFixture, testFixedArrayErrorHandling) {
	try {
		FixArray<int, 10> d;
		d[11];
		FAIL();
	}
	catch (InvalidSize e) {
		FAIL();
	}
	catch (InvalidIndexValue e) {
		ASSERT_THAT(e.what(), "Invalid Index Value = [11]\n");
	}
	catch (std::exception e) {
		FAIL();
	}
}

TEST_F(ArrayTestFixture, testFixedArray) {
	FixArray<int, 10> testArray;
	{
		testing::internal::CaptureStdout();
		std::cout << testArray;
		std::ostringstream os, os2;
		testArray.print(os);
		testArray.print(os2, 5);
		std::string output = testing::internal::GetCapturedStdout();
		ASSERT_THAT("[ 0 0 0 0 0 0 0 0 0 0 ]", output);
		ASSERT_THAT("[ 0 0 0 0 0 0 0 0 0 0 ]", os.str());
		ASSERT_THAT("[ 0 0 0 0 0 ]", os2.str());
	}
	for (size_t i = 0; i < 10; i++) {
		testArray[i] = i;
	}
	{
		testing::internal::CaptureStdout();
		std::cout << testArray;
		std::ostringstream os, os2;
		testArray.print(os);
		testArray.print(os2, 5);
		std::string output = testing::internal::GetCapturedStdout();
		ASSERT_THAT("[ 0 1 2 3 4 5 6 7 8 9 ]", output);
		ASSERT_THAT("[ 0 1 2 3 4 5 6 7 8 9 ]", os.str());
		ASSERT_THAT("[ 0 1 2 3 4 ]", os2.str());
	}
}