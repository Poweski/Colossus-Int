#pragma once
#include <string>
#include "ColossusInt.h"

class Test
{
private:
	ColossusInt object12;
	ColossusInt objectMinus12;
	ColossusInt object3;
	ColossusInt objectMinus3;
	ColossusInt object0;
	ColossusInt object21;
	ColossusInt object7;
	ColossusInt object3456;
	ColossusInt result;

	void printAndAssertResult(const std::string expected);
	void printSuccessMessage(const std::string nameOfOperation);
	void printTestName(const std::string nameOfTest);

public:
	Test();

	void testOfAddition();
	void testOfSubtraction();
	void testOfMultiplication();
	void testOfDivision();
	void runAllTests();
};

const int number12 = 12;
const int numberMinus12 = -12;
const int number3 = 3;
const int numberMinus3 = -3;
const int number0 = 0;
const int number21 = 21;
const int number7 = 7;
const int number3456 = 3456;

const std::string string15 = "15";
const std::string stringMinus15 = "-15";
const std::string string9 = "9";
const std::string stringMinus9 = "-9";
const std::string string6 = "6";
const std::string stringMinus6 = "-6";
const std::string stringMinus3 = "-3";
const std::string string0 = "0";
const std::string string36 = "36";
const std::string stringMinus36 = "-36";
const std::string string72576 = "72576";
const std::string string4 = "4";
const std::string stringMinus4 = "-4";
const std::string stringMinus1 = "-1";
const std::string string493 = "493";

const std::string testOf = "Test of ";
const std::string semicolon = ": ";
const std::string stringActual = "Actual: ";
const std::string stringExpected = ", Expected: ";
const std::string testCompletedSuccessfully = " test completed successfully!\n";
const std::string addition = "Addition";
const std::string subtraction = "Subtraction";
const std::string multiplication = "Multiplication";
const std::string division = "Division";