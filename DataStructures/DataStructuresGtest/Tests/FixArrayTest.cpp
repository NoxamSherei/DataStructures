#pragma once
#include "..\pch.h"
#include "..\..\DataStructures\inc\FixedArray.h"
#include <iostream>
#include <array>
class ArrayTestFixture :public ::testing::Test {
public:
};

TEST_F(ArrayTestFixture, testFixedArrayConstructorsAndAssaigment) {
	FixArray<int, 10> source;
	source.fill(0);
	EXPECT_THAT(source.getSize(),10);
	source[2] = 22;
	//CopyConstructor
	FixArray<int, 10> arrayA(source);
	arrayA[1] = 10;
	ASSERT_NE(source.getBegin(), arrayA.getBegin());
	ASSERT_NE(nullptr, arrayA.getBegin());
	EXPECT_EQ(source[1], 0);
	EXPECT_EQ(source[2], 22);
	EXPECT_EQ(arrayA[1], 10);
	EXPECT_EQ(arrayA[2], 22);
	//CopyAssaigment
	FixArray<int, 10> arrayB = source;
	arrayB[1] = 20;
	ASSERT_NE(source.getBegin(), arrayB.getBegin());
	ASSERT_NE(nullptr, arrayB.getBegin());
	EXPECT_EQ(source[1], 0);
	EXPECT_EQ(source[2], 22);
	EXPECT_EQ(arrayB[1], 20);
	EXPECT_EQ(arrayB[2], 22);
	//MoveConstructor
	auto lastPosA = arrayA.getBegin();
	FixArray<int, 10> arrayC(std::move(arrayA));
	ASSERT_NE(arrayC.getBegin(), arrayA.getBegin());
	ASSERT_THAT(arrayA.getBegin(), nullptr);
	ASSERT_THAT(arrayC.getBegin(), lastPosA);
	//MoveAssaigment
	auto lastPosB = arrayB.getBegin();
	FixArray<int, 10> arrayD = std::move(arrayB);
	ASSERT_NE(arrayD.getBegin(), arrayB.getBegin());
	ASSERT_THAT(arrayB.getBegin(), nullptr);
	ASSERT_THAT(arrayD.getBegin(), lastPosB);

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
	catch (ErrorInvalidSize e) {
		FAIL();
	}
	catch (ErrorInvalidIndexValue e) {
		ASSERT_THAT(e.what(), "Invalid Index Value = [11]\n");
	}
	catch (std::exception e) {
		FAIL();
	}
}
TEST_F(ArrayTestFixture, testFixedArrayOperators) {
	FixArray<int, 10> testArray1;
	FixArray<int, 10> testArray2;
	testArray1.fill(5);
	testArray2.fill(5);
	//std::cin >> testArray2;
	testing::internal::CaptureStdout();
	std::cout << testArray1 << std::endl;
	std::cout << testArray2 << std::endl;
	std::cout << testArray1 << "+" << testArray2 << "=" << (testArray1 + testArray2) << std::endl;
	std::cout << testArray1 << "-" << testArray2 << "=" << (testArray1 - testArray2) << std::endl;
	std::cout << testArray1 << "*" << testArray2 << "=" << (testArray1 * testArray2) << std::endl;
	std::cout << testArray1 << "/" << testArray2 << "=" << (testArray1 / testArray2) << std::endl;
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected =
		"[ 5 5 5 5 5 5 5 5 5 5 ]\n"
		"[ 5 5 5 5 5 5 5 5 5 5 ]\n"
		"[ 5 5 5 5 5 5 5 5 5 5 ]+[ 5 5 5 5 5 5 5 5 5 5 ]=[ 10 10 10 10 10 10 10 10 10 10 ]\n"
		"[ 5 5 5 5 5 5 5 5 5 5 ]-[ 5 5 5 5 5 5 5 5 5 5 ]=[ 0 0 0 0 0 0 0 0 0 0 ]\n"
		"[ 5 5 5 5 5 5 5 5 5 5 ]*[ 5 5 5 5 5 5 5 5 5 5 ]=[ 25 25 25 25 25 25 25 25 25 25 ]\n"
		"[ 5 5 5 5 5 5 5 5 5 5 ]/[ 5 5 5 5 5 5 5 5 5 5 ]=[ 1 1 1 1 1 1 1 1 1 1 ]\n";
	ASSERT_THAT(expected, output);
}

TEST_F(ArrayTestFixture, testFixedArray) {
	FixArray<int, 10> testArray;
	testArray.fill(0);
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
		std::ostringstream os, os2,os3;
		testArray.print(os);
		testArray.print(os2, 5);
		testArray.print(os3, 4, 8);
		std::string output = testing::internal::GetCapturedStdout();
		ASSERT_THAT("[ 0 1 2 3 4 5 6 7 8 9 ]", output);
		ASSERT_THAT("[ 0 1 2 3 4 5 6 7 8 9 ]", os.str());
		ASSERT_THAT("[ 4 5 6 7 ]", os3.str());
	}
}