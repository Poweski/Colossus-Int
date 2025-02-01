#pragma once
#include <string>

class ColossusInt
{
private:

    int* digits;

    int size;

    void decreaseSize(ColossusInt& object);

public:

    ColossusInt();

    ~ColossusInt();

    void operator=(const int value);

    void operator=(const ColossusInt& other);

    ColossusInt operator+(const ColossusInt& other);

    ColossusInt operator-(const ColossusInt& other);

    ColossusInt operator*(ColossusInt& other);

    ColossusInt operator/(ColossusInt& other);

    int compareTo(const ColossusInt& other);

    std::string toStr();
};

const int minimalSize = 2;
const int divider = 10;

const char plusSign = '+';
const char minusSign = '-';
const char charZero = '0';

const std::string stringZero = "0";
const std::string divisionErrorMessage = "Error! Division by 0!";
