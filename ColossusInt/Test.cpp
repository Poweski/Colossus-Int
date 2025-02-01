#include <iostream>
#include <cassert>
#include "Test.h"

Test::Test()
{
    object12 = number12;
    objectMinus12 = numberMinus12;
    object3 = number3;
    objectMinus3 = numberMinus3;
    object0 = number0;
    object21 = number21;
    object7 = number7;
    object3456 = number3456;
}

void Test::printTestName(const std::string nameOfTest)
{
    std::cout << testOf << nameOfTest << semicolon << std::endl;
}

void Test::printAndAssertResult(const std::string expected)
{
    std::cout << stringActual << result.toStr() << stringExpected << expected << std::endl;
    assert(result.toStr() == expected);
}

void Test::printSuccessMessage(const std::string nameOfOperation)
{
    std::cout << std::endl << nameOfOperation << testCompletedSuccessfully << std::endl;
}

void Test::testOfAddition()
{
    printTestName(addition);

    result = object12 + object3;
    printAndAssertResult(string15);

    result = object12 + objectMinus3;
    printAndAssertResult(string9);

    result = objectMinus12 + object3;
    printAndAssertResult(stringMinus9);

    result = objectMinus12 + objectMinus3;
    printAndAssertResult(stringMinus15);

    result = object3 + object3;
    printAndAssertResult(string6);

    result = object3 + objectMinus3;
    printAndAssertResult(string0);

    result = objectMinus3 + objectMinus3;
    printAndAssertResult(stringMinus6);

    result = objectMinus3 + object0;
    printAndAssertResult(stringMinus3);

    printSuccessMessage(addition);
}

void Test::testOfSubtraction()
{
    printTestName(subtraction);

    result = object12 - object3;
    printAndAssertResult(string9);

    result = object12 - objectMinus3;
    printAndAssertResult(string15);

    result = objectMinus12 - object3;
    printAndAssertResult(stringMinus15);

    result = objectMinus12 - objectMinus3;
    printAndAssertResult(stringMinus9);

    result = object3 - object3;
    printAndAssertResult(string0);

    result = object3 - objectMinus3;
    printAndAssertResult(string6);

    result = objectMinus3 - objectMinus3;
    printAndAssertResult(string0);

    result = objectMinus3 - object0;
    printAndAssertResult(stringMinus3);

    result = object3 - object12;
    printAndAssertResult(stringMinus9);

    printSuccessMessage(subtraction);
}

void Test::testOfMultiplication()
{
    printTestName(multiplication);

    ColossusInt a, b;
    a = 1254722;
    b = 3462462;
    result = a * b;
    printAndAssertResult("4344427245564");

    result = object12 * object3;
    printAndAssertResult(string36);

    result = object12 * objectMinus3;
    printAndAssertResult(stringMinus36);

    result = objectMinus12 * objectMinus3;
    printAndAssertResult(string36);

    result = objectMinus12 * object0;
    printAndAssertResult(string0);

    result = object21 * object3456;;
    printAndAssertResult(string72576);

    printSuccessMessage(multiplication);
}

void Test::testOfDivision()
{
    printTestName(division);

    result = object12 / object3;
    printAndAssertResult(string4);

    result = object12 / objectMinus3;
    printAndAssertResult(stringMinus4);

    result = objectMinus12 / objectMinus3;
    printAndAssertResult(string4);

    result = objectMinus3 / object12;
    printAndAssertResult(string0);

    result = object21 / objectMinus12;
    printAndAssertResult(stringMinus1);

    result = object3456 / object7;
    printAndAssertResult(string493);

    try
    {
        result = objectMinus12 / object0;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }

    printSuccessMessage(division);
}

void Test::runAllTests()
{
    testOfAddition();
    testOfSubtraction();
    testOfMultiplication();
    testOfDivision();
}