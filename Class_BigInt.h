#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

class BigInt
{
private:
	int* digits;
	long long size;
	bool sign;
public:
	static const int base = 1000000000;
	static const int base_length = 9;

	BigInt();
	BigInt(int);
	BigInt(std::string);
	BigInt(const BigInt&);
	~BigInt();

	void from_string_to_array(const std::string&);

	BigInt operator+() const
	{
		return *this;
	};
	BigInt operator-() const
	{
		BigInt tmp = *this;
		tmp.sign = (false == (*this).sign);
		return tmp;
	};


	BigInt& operator=(const BigInt& number)
	{
		if ((*this).size != 0)
			delete (*this).digits;
		(*this).digits = new int[number.size];
		(*this).size = number.size;
		(*this).sign = number.sign;
		for (int i = 0; i < size; i++)
			(*this).digits[i] = number.digits[i];
		return (*this);
	};
	BigInt& operator~() const{};

	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);

	BigInt& operator++();
	const BigInt operator++(int);
	BigInt& operator--();
	const BigInt operator--(int);

	operator std::string() const
	{
		std::string str;
		int i = 0;
		if (sign == false && digits[0] != 0)
			str += '-';
		while (digits[i] == 0 && i != (size - 1))
			i++;
		str += std::to_string(digits[i]);
		for (int j = i + 1; j < size; j++)
		{
			int len = 0;
			int num = digits[j];
			while (num > 0)
			{
				num /= 10;
				len++;
			}
			while (len != 9)
			{
				str += '0';
				len++;
			}
			str += std::to_string(digits[j]);
		}
		return str;
	}
	operator int() const
	{
		int number = 0;
		if ((*this).size >= 2)
		{
			number += (*this).digits[size - 1];
			if (((*this).sign == false) && (number <= abs(INT_MIN % base)))
			{
				if ((*this).digits[size - 2] % 10 < 3)
					number += ((*this).digits[size - 2] % 10) * base;
				return -number;
			}
			if (((*this).sign == true) && (number <= INT_MAX % base))
			{
				if ((*this).digits[size - 2] % 10 < 3)
					number += ((*this).digits[size - 2] % 10) * base;
				return number;
			}
			if ((*this).sign == true)
				return number;
			else
				return -number;
		}
		if ((*this).size == 1)
		{
			number = digits[0];
			if ((*this).sign == true)
				return number;
			else
				return -number;
		}
	}

	bool operator==(const BigInt& number) const;
	bool operator!=(const BigInt& number) const;
	bool operator>(const BigInt& number) const;
	bool operator<(const BigInt& number) const;
	bool operator<=(const BigInt& number) const;
	bool operator>=(const BigInt& number) const;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);

std::ostream& operator <<(std::ostream& o, const BigInt& i);
