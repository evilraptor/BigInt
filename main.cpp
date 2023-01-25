#include "Class_BigInt.h"

int main()
{
    //std::string str1 = "4574988923784";
    //std::string str2 = "7892657887452";
    //BigInt number1 = BigInt(str1);
    //BigInt number2 = BigInt(str2);

    //std::cout << number1 + BigInt(2);

    BigInt number3 = BigInt(-2);
    BigInt number4 = BigInt(-4);
    number3 *= number4;
    std::cout << number3;

    //std::cout << ((BigInt(1) * BigInt(0))==BigInt(0));
    //std::cout << ((BigInt(2) + BigInt(3)) * BigInt(4));
    //std::cout << ((BigInt(2) + BigInt(3)) * BigInt(0));
    return 0;
}
