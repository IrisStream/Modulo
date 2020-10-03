#include "bigint.h"
#include <conio.h>

int main()
{
    BigInt a(3);
    BigInt b(5);
    BigInt c(6);
    gcd(a,c).printBit();
    getch();
    return 0;
}