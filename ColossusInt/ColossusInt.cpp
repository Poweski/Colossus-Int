#include <iostream>
#include "ColossusInt.h"

ColossusInt::ColossusInt()
{
    digits = nullptr;
    size = 0;
}

ColossusInt::~ColossusInt()
{
    delete[] digits;
}

void ColossusInt::operator=(const int value)
{
    std::string strValue = std::to_string(value);

    delete[] digits;

    if (value >= 0)
    {
        size = strValue.length() + 1;
        digits = new int[size];

        digits[0] = plusSign;

        for (int i = size - 1; i > 0; i--)
        {
            digits[size - i] = strValue[i - 1] - charZero;
        }
    }
    else
    {
        size = strValue.length();
        digits = new int[size];

        digits[0] = minusSign;

        for (int i = size - 1; i > 0; i--)
        {
            digits[size - i] = strValue[i] - charZero;
        }
    }
}

void ColossusInt::operator=(const ColossusInt& other)
{
    delete[] digits;

    size = other.size;
    digits = new int[size];

    for (int i = 0; i < size; i++)
    {
        digits[i] = other.digits[i];
    }
}

ColossusInt ColossusInt::operator+(const ColossusInt& other)
{
    ColossusInt result;

    if (digits[0] == other.digits[0])
    {
        int carry = 0, sum = 0;
        int maxSize = (size > other.size ? size : other.size) + 1;
        int* newDigits = new int[maxSize];

        result.size = maxSize;

        for (int i = 1; i < maxSize - 1; i++)
        {
            sum = (i < size ? digits[i] : 0) + (i < other.size ? other.digits[i] : 0) + carry;
            newDigits[i] = sum % divider;
            carry = sum / divider;
        }

        result.digits = newDigits;

        if (carry > 0)
        {
            newDigits[maxSize] = carry;
        }
        else
        {
            decreaseSize(result);
        }

        result.digits[0] = digits[0];
    }
    else
    {
        const ColossusInt* bigger = nullptr;
        const ColossusInt* smaller = nullptr;

        int maxSize = (size > other.size ? size : other.size);

        int flag = compareTo(other);

        if (flag == 0)
        {
            result.digits = new int[minimalSize];
            result.digits[1] = 0;
            result.size = minimalSize;
        }
        else
        {
            if (flag == 1)
            {
                bigger = this;
                smaller = &other;
            }
            else
            {
                bigger = &other;
                smaller = this;
            }

            int* newDigits = new int[maxSize];
            result.size = maxSize;

            int credit = 0, difference = 0;

            for (int i = 1; i < maxSize; i++)
            {
                difference = bigger->digits[i] - (i < smaller->size ? smaller->digits[i] : 0) - credit;
                if (difference < 0)
                {
                    credit = 1;
                    difference += divider;
                }
                else
                {
                    credit = 0;
                }
                newDigits[i] = difference;
            }

            result.digits = newDigits;

            if (newDigits[maxSize - 1] == 0)
            {
                decreaseSize(result);
            }
        }

        if (flag == 0)
        {
            result.digits[0] = plusSign;
        }
        else if (flag == 1)
        {
            result.digits[0] = digits[0];
        }
        else
        {
            result.digits[0] = other.digits[0];
        }
    }

    return result;
}

ColossusInt ColossusInt::operator-(const ColossusInt& other)
{
    ColossusInt result, temp;

    temp = other;

    if (temp.digits[0] == plusSign)
    {
        temp.digits[0] = minusSign;
    }
    else
    {
        temp.digits[0] = plusSign;
    }

    result = *this + temp;

    return result;
}

ColossusInt ColossusInt::operator*(ColossusInt& other)
{
    ColossusInt result;

    if (toStr() == stringZero || other.toStr() == stringZero)
    {
        int* newDigits = new int[minimalSize];
        newDigits[0] = 0;
        newDigits[1] = 0;
        result.size = minimalSize;
        result.digits = newDigits;
        return result;
    }

    int maxSize = size + other.size - 1;
    int* newDigits = new int[maxSize];

    for (int i = 1; i < maxSize; i++)
    {
        newDigits[i] = 0;
    }

    if (digits[0] == other.digits[0])
    {
        newDigits[0] = plusSign;
    }
    else
    {
        newDigits[0] = minusSign;
    }

    int product = 0, carry = 0;

    for (int i = 1; i < size; i++)
    {
        product = carry = 0;

        for (int j = 1; j < other.size; j++)
        {
            product = digits[i] * other.digits[j] + carry;
            carry = (newDigits[j + i - 1] + product) / divider;
            newDigits[j + i - 1] = (newDigits[j + i - 1] + product) % divider;
        }

        if (carry > 0)
        {
            newDigits[other.size + i - 1] += carry;
        }
    }

    result.size = maxSize;
    result.digits = newDigits;

    if (carry > 0)
    {
        newDigits[maxSize - 1] = carry;
    }
    else
    {
        decreaseSize(result);
    }

    return result;
}

ColossusInt ColossusInt::operator/(ColossusInt& other)
{
    if (other.toStr() == stringZero)
    {
        throw std::invalid_argument(divisionErrorMessage);
    }

    ColossusInt result, absoluteValueOfOther;

    absoluteValueOfOther = other;
    absoluteValueOfOther.digits[0] = plusSign;

    if (other.size > size)
    {
        result.size = minimalSize;
        result.digits = new int[minimalSize];
        result.digits[0] = plusSign;
        result.digits[1] = 0;
        return result;
    }
    ColossusInt temp, previousTemp, multiplier;

    multiplier = divider;

    temp.size = other.size;
    temp.digits = new int[other.size];
    temp.digits[0] = plusSign;

    int differenceInSize = size - other.size;

    result.size = differenceInSize + minimalSize;
    result.digits = new int[differenceInSize + minimalSize];

    for (int i = other.size - 1; i > 0; i--)
    {
        temp.digits[i] = digits[i + differenceInSize];
    }

    int counter = differenceInSize + 1;
    bool isFirstPlace = true;

    while (counter > 0)
    {
        int resultCounter = -1;

        while (temp.digits[0] != minusSign)
        {
            previousTemp = temp;
            temp = temp - absoluteValueOfOther;

            resultCounter++;
        }

        temp = previousTemp * multiplier;
        temp.digits[1] = digits[counter - 1];

        if (resultCounter == 0 && isFirstPlace)
        {
            int* newDigits = new int[result.size - 1];

            for (int i = 0; i < result.size - 1; i++)
            {
                newDigits[i] = result.digits[i];
            }

            delete[] result.digits;
            result.digits = newDigits;
            result.size--;
        }
        else
        {
            result.digits[counter] = resultCounter;
        }

        isFirstPlace = false;
        counter--;
    }

    if (digits[0] == other.digits[0])
    {
        result.digits[0] = plusSign;
    }
    else
    {
        result.digits[0] = minusSign;
    }

    return result;
}

int ColossusInt::compareTo(const ColossusInt& other)
{
    if (size > other.size)
    {
        return 1;
    }
    else if (other.size > size)
    {
        return -1;
    }
    else
    {
        int maxSize = (size > other.size ? size : other.size);

        for (int i = maxSize - 1; i > 0; i--)
        {
            if (digits[i] > other.digits[i])
            {
                return 1;
            }
            else if (digits[i] < other.digits[i])
            {
                return -1;
            }
        }
    }

    return 0;
}

void ColossusInt::decreaseSize(ColossusInt& object)
{
    int newSize = object.size - 1;
    int* newDigits = new int[newSize];

    for (int i = 0; i < newSize; i++)
    {
        newDigits[i] = object.digits[i];
    }

    delete[] object.digits;
    object.digits = newDigits;
    object.size = newSize;
}

std::string ColossusInt::toStr()
{
    std::string result;

    if (digits[0] == minusSign)
    {
        result = minusSign;
    }

    for (int i = size - 1; i > 0; i--)
    {
        result += std::to_string(digits[i]);
    }

    return result;
}
