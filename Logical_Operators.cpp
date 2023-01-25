#include "Class_BigInt.h"

bool BigInt::operator==(const BigInt& number) const
{
	if ((*this).sign != number.sign)
		return false;

	if ((*this).size != number.size)
		return false;

	for (int i = 0; i < number.size; i++)
		if ((*this).digits[i] != number.digits[i])
			return false;

	return true;
}

bool BigInt::operator!=(const BigInt& number) const
{
	return !((*this) == number);
}

bool BigInt::operator>(const BigInt& number) const
{
	if ((*this) == number)
		return false;

	if ((*this).sign == false && number.sign == true)
		return false;
	if ((*this).sign == true && number.sign == false)
		return true;

	if ((*this).sign == true)
	{
		if ((*this).size < number.size)
			return false;
		if ((*this).size > number.size)
			return true;
		for (int i = 0; i < (*this).size; i++)
		{
			if ((*this).digits[i] > number.digits[i])
				return true;
			if ((*this).digits[i] < number.digits[i])
				return false;
		}
	}

	if ((*this).sign == false)
	{
		if ((*this).size < number.size)
			return true;
		if ((*this).size > number.size)
			return false;
		for (int i = 0; i < (*this).size; i++)
			if ((*this).digits[i] > number.size)
				return false;
	}
}


bool BigInt::operator<(const BigInt& number) const
{
	if ((*this) != number && !((*this) > number))
		return true;
	return false;
}

bool BigInt::operator<=(const BigInt& number) const
{
	if ((*this) < number || (*this) == number)
		return true;
	return false;
}

bool BigInt::operator>=(const BigInt& number) const
{
	if ((*this) > number || (*this) == number)
		return true;
	return false;
}
