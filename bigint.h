#ifndef __BIGINT_H__
#define __BIGINT_H__
#include <iostream>
#include <algorithm>

class BigInt{
private:
    int * data;
    int size;
    static const int numSize = 32;
    static const int maxSize = 32;
    static int getBit(int ,int);
    static void setBit(int&, int, bool);
public:
    //Ctor
    BigInt();
    BigInt(int);
    BigInt(const BigInt&);
    BigInt reverse();

    //Operator
    bool getBit(int);
    void setBit(int, bool);
    int getSize();
    void setSize(int);
    void printBit();
    void operator=(const BigInt &);
    void operator=(int);
    friend bool operator<(BigInt&, BigInt&);
    friend bool operator>(BigInt&, BigInt&);
    friend bool operator<=(BigInt&, BigInt&);
    friend bool operator>=(BigInt&, BigInt&);
    friend bool operator!=(BigInt&, BigInt&);
    friend bool operator==(BigInt&, BigInt&);
    friend BigInt operator+(BigInt&, BigInt&);
    friend BigInt operator-(BigInt&, BigInt&);
    friend BigInt addMod(BigInt&, BigInt&, BigInt&);
    friend BigInt mulMod(BigInt&, BigInt&, BigInt&);
    friend BigInt gcd(BigInt& , BigInt&);
    //Dtor
    ~BigInt();
};

#endif