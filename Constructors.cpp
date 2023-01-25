#include "Class_BigInt.h"

std::ostream& operator <<(std::ostream& o, const BigInt& i)
{
	std::string str = std::string(i);
	for (long long j = 0; j < str.size(); j++)
		o.put(str[j]);
	return o;
};

BigInt::BigInt()
{
	sign = true;
	size = 0;
}

BigInt::BigInt(int num)
{
	if (num >= base)
	{
		digits = new int[2];
		digits[0] = abs(num / base);
		digits[1] = abs(num % base);
		size = 2;
	}
	else
	{
		digits = new int[1];
		digits[0] = abs(num);
		size = 1;
	}
	sign = (num >= 0);
}

BigInt::BigInt(std::string str)
{
	if (str.empty() || (str.size() == 1 && str[0] == '-'))
		throw std::invalid_argument("Invalid syntax. String doesn't contain a number.");

	if (str[0] == '-')
	{
		str.erase(str.begin());
		sign = false;
	}
	else
		sign = true;

	for (int str_position = 0; str_position < str.size(); str_position++)
	{
		if (str[str_position] < '0' || str[str_position] > '9')
			throw std::invalid_argument("Invalid syntax. String contains unacceptable symbols.");
	}

	while (str.size() != 1 and str[0] == '0')
		str.erase(str.begin());

	if (str.size() % base_length == 0)
		size = str.size() / base_length;
	else
		size = str.size() / base_length + 1;

	digits = new int[size];
	from_string_to_array(str);
}

BigInt::BigInt(const BigInt& number)
{
	digits = new int[number.size];
	(*this).size = number.size;
	(*this).sign = number.sign;
	for (int i = 0; i < size; i++)
		(*this).digits[i] = number.digits[i];
}

BigInt::~BigInt()
{
	delete[] digits;
}
