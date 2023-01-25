#include "Class_BigInt.h"

void BigInt::from_string_to_array(const std::string& str)
{
	for (long long str_position = str.size() - 1, res_position = size - 1; str_position >= 0; str_position = str_position - base_length, res_position = res_position - 1)
		if (((str_position + 1) - base_length) <= 0)
			digits[res_position] = stoi(str.substr(0, str_position + 1));
		else
			digits[res_position] = stoi(str.substr(str_position - base_length + 1, base_length));
}
