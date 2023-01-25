#include "Class_BigInt.h"

BigInt operator +(const BigInt& number1, const BigInt& number2)
{
	BigInt tmp = number1;
	return (tmp += number2);
}

BigInt operator -(const BigInt& number1, const BigInt& number2)
{
	BigInt tmp = number1;
	return (tmp -= number2);
}

BigInt operator *(const BigInt& number1, const BigInt& number2)
{
	BigInt tmp = number1;
	return (tmp *= number2);
}

BigInt& BigInt::operator +=(const BigInt& other) //*this += other
{
	if (sign == other.sign)
	{
		int max = std::max(size, other.size);
		int* tmp_digits = new int[max + 1];
		int tmp_size = max + 1;
		std::fill(tmp_digits, tmp_digits + tmp_size, 0);

		long long sum = 0;
		int add_next_digit = 0;
		long long i = size - 1;
		long long j = other.size - 1;
		long long k = tmp_size - 1;
		for (i, j, k; ((i >= 0) && (j >= 0)); i--, j--, k--)
		{
			sum = (long long)digits[i] + (long long)other.digits[j] + add_next_digit;
			add_next_digit = sum / base;
			tmp_digits[k] = sum % base;
		}
		if (i >= 0)
		{
			for (i; i >= 0; i--, k--)
			{
				sum = (long long)digits[i] + (long long)add_next_digit;
				add_next_digit = sum / base;
				tmp_digits[k] = sum % base;
			}
		}
		else
		{
			if (j >= 0)
			{
				for (j; j >= 0; j--, k--)
				{
					sum = other.digits[j] + add_next_digit;
					add_next_digit = sum / base;
					tmp_digits[k] = sum % base;
				}
			}
		}
		if (add_next_digit != 0)
			tmp_digits[k] = add_next_digit;

		int new_size = 0;
		if (tmp_digits[0] == 0)
			new_size = tmp_size - 1;
		else
			new_size = tmp_size;

		delete[] digits;
		digits = new int[new_size];
		for (int n = tmp_size - 1, m = new_size - 1; m >= 0; n--, m--)
			digits[m] = tmp_digits[n];
		size = new_size;
		return *this;
	}
	if (!sign && other.sign)
	{
		BigInt tmp = other;
		sign = true;
		tmp -= *this;
		*this = tmp;
		return *this;
	}
	else
	{
		BigInt tmp = other;
		tmp.sign = true;
		*this -= tmp;
		return *this;
	}
}

BigInt& BigInt::operator -=(const BigInt& other)
{
	if (sign && other.sign)
	{
		if (*this < other)
		{
			BigInt tmp = other;
			tmp -= *this;
			*this = tmp;
			(*this).sign = false;
			return (*this);
		}
		int max = std::max(size, other.size);
		int* tmp_digits = new int[max];
		int tmp_size = max;
		std::fill(tmp_digits, tmp_digits + tmp_size, 0);

		long long difference = 0;
		//int add_next_digit = 0;
		long long i = size - 1;
		long long j = other.size - 1;
		long long k = tmp_size - 1;

		for (i, j, k; ((i >= 0) && (j >= 0)); i--, j--, k--)
		{
			difference = (long long)digits[i] - (long long)other.digits[j];
			if (difference >= 0)
				tmp_digits[k] = difference;
			else
			{
				tmp_digits[k] = difference + base;
				for (long long h = i - 1; true; h--)
				{
					if (digits[h] == 0)
						digits[h] = base - 1;
					else
					{
						digits[h] -= 1;
						break;
					}
				}
			}
		}
		if (i >= 0)
		{
			for (i; i >= 0; i--, k--)
				tmp_digits[k] = digits[i];
		}

		int new_size = tmp_size;

		for (int n = 0; n < tmp_size - 1; n++)
		{
			if (tmp_digits[n] == 0)
				new_size--;
			else
				break;
		}

		delete[] digits;
		digits = new int[new_size];
		for (int n = tmp_size - 1, m = new_size - 1; m >= 0; n--, m--)
			digits[m] = tmp_digits[n];
		size = new_size;
		return *this;
	}
	else if (!sign && !other.sign)
	{
		BigInt tmp = other;
		tmp.sign = true;
		*this += tmp;
		return *this;
	}
	else if (!sign && other.sign)
	{
		sign = true;
		*this += other;
		sign = false;
		return *this;
	}
	else
	{
		sign = false;
		*this += other;
		sign = true;
		return *this;
	}

}

BigInt& BigInt::operator *=(const BigInt& other)
{
	if (sign && other.sign) {
		//BigInt first_number = number1;
		//BigInt second_number = number2;
		//BigInt result_number;
		int* tmp_digits = new int[size + other.size];
		int tmp_size = size + other.size;
		std::fill(tmp_digits, tmp_digits + tmp_size, 0);
		long long mod = 0;
		long long prev = 0;
		for (long long i = other.size - 1; i >= 0; i--)
		{
			for (long long j = size - 1; j >= 0; j--)
			{
				long long tmp = (long long)digits[j] * (long long)other.digits[i] + mod;

				prev = tmp_digits[i + j + 1];
				tmp_digits[i + j + 1] = (prev + tmp) % base;
				mod = (prev + tmp) / base;

				prev = tmp_digits[i + j];
				tmp_digits[i + j] = (prev + mod) % base;
				mod = (prev + mod) / base;
			}
		}
		if (mod != 0)
			tmp_digits[0] += mod;
		sign = true;


		int new_size = tmp_size;

		for (int n = 0; n < tmp_size - 1; n++)
		{
			if (tmp_digits[n] == 0)
				new_size--;
			else
				break;
		}
		delete[] digits;
		digits = new int[new_size];
		for (int n = tmp_size - 1, m = new_size - 1; m >= 0; n--, m--)
			digits[m] = tmp_digits[n];
		size = new_size;
		return *this;



		//return *this;
	}
	else if (!sign && !other.sign)
	{
		BigInt tmp = other;
		tmp.sign = true;
		sign = true;
		*this *= tmp;
		return *this;
	}
	else if (!sign && other.sign)
	{
		sign = true;
		*this *= other;
		sign = false;
		return *this;
	}
	else
	{
		BigInt tmp = other;
		tmp.sign = true;
		*this *= tmp;
		sign = false;
		return *this;
	}
}
