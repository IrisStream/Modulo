#include "bigint.h"

BigInt::BigInt(){
    data = new int[maxSize];
    for(int i = 0;i<maxSize;i++)
        data[i] = 0;
    size = 1;
}

BigInt::BigInt(int num) :BigInt(){
    size = 0;
    while(num != 0){
        setBit(size, num%2);
        size++;
        num /= 2;
    }
}

BigInt::BigInt(const BigInt &src) :BigInt(){
    if(this == &src)
        return;
    size = src.size;
    for(int i = 0;i<maxSize;i++){
        data[i] = src.data[i]; 
    }
}

BigInt BigInt::reverse(){
    BigInt ans;
    ans.size = size;
    for(int i = 0;i < size;i++){
        ans.setBit(i, this->getBit(size - i - 1));
    }
    return ans;
}

int BigInt::getBit(int num, int pos){
    if(pos < 0)
        return -1;
    return (num >> pos) & 1;
}

void BigInt::setBit(int& num, int pos, bool value){
    if(pos < 0)
        return;
    if(getBit(num, pos) == value)
        return;
    num = num ^ (1 << pos);
}

bool BigInt::getBit(int pos){
    return getBit(data[pos / numSize], pos % numSize);
}

void BigInt::setBit(int pos, bool value){
    setBit(data[pos / numSize], pos % numSize, value);
}

int BigInt::getSize(){
    return size;
}

void BigInt::setSize(int newSize){
    size = newSize;
}

void BigInt::printBit(){
    for(int i = size - 1;i>=0;i--){
        if(getBit(i))
        {
            std::cout << 1;
        } else
        {
            std::cout << 0;
        }
        
    }
    std::cout << std::endl;
}

void BigInt::operator=(const BigInt & src){
    if(this == &src)
        return;
    size = src.size;
    for(int i = 0;i< maxSize;i++){
        data[i] = src.data[i];
    }
}

void BigInt::operator=(int num){
    BigInt src(num);
    operator=(src);
}

bool operator<(BigInt& num1, BigInt& num2){
    if(num1.size < num2.size)
        return true;
    else if(num1.size > num2.size)
        return false;
    else
    {
        for(int i = num1.size-1;i>=0;i--)
        {
            if(num1.getBit(i) > num2.getBit(i))
                return false;
            if(num1.getBit(i) < num2.getBit(i))
                return true;
        }
    }    
    return false;
}

bool operator>(BigInt& num1, BigInt& num2){
    if(num2 < num1)
        return true;
    return false;
}

bool operator<=(BigInt& num1, BigInt& num2){
    if(num1 > num2)
        return false;
    return true;
}

bool operator>=(BigInt& num1, BigInt& num2){
    if(num1 < num2)
        return false;
    return true;
}

bool operator!=(BigInt& num1, BigInt& num2){
    if(num1 < num2 || num1 > num2)
        return true;
    return false;
}

bool operator==(BigInt& num1, BigInt& num2){
    if(num1 != num2);
        return false;
    return true;
}

BigInt operator+(BigInt& num1, BigInt& num2){
    BigInt ans;
    int memo = 0;
    ans.size = std::max(num1.size, num2.size);
    for(int i = 0;i < ans.size;i++)
    {
        memo = memo + num1.getBit(i) + num2.getBit(i);
        ans.setBit(i, memo & 1);
        memo = memo >> 1;
    }
    if(memo){
        ans.setBit(ans.size, memo);
        ans.size++;
    }
    return ans;
}

BigInt operator-(BigInt& num1, BigInt& num2){
    BigInt ans;
    int memo = 0;
    ans.size = std::max(num1.size, num2.size);
    for(int i = 0;i < ans.size;i++){
        memo = num1.getBit(i) - num2.getBit(i) - memo;
        if(memo < 0){
            ans.setBit(i, memo + 2);
            memo = 1;
        } else{
            ans.setBit(i, memo);
            memo = 0;
        }
    }
    while(ans.getBit(ans.size-1) == false && ans.size > 1)
        ans.size--;
    return ans;
}

BigInt addMod(BigInt& num1, BigInt& num2, BigInt& num3){
    BigInt ans = num1 + num2;
    while(ans >= num3){
        ans = ans - num3;
    }
    return ans;
}

BigInt mulMod(BigInt& num1, BigInt& num2, BigInt& num3){
    BigInt ans;
    BigInt temp = num1.reverse();
    for(int i = 0;i < num2.size;i++){
        if(num2.getBit(i) == true){
            BigInt rev = temp.reverse();
            ans = addMod(ans, rev, num3);
        }
        temp.size = temp.size + 1;
    }
    return ans;
}

BigInt gcd(BigInt& num1, BigInt& num2){
    while(num1 != num2){
        if(num1 > num2)
            num1 = num1 - num2;
        else
            num2 = num2 - num1;
    }
    return num1;
}

BigInt::~BigInt(){
    delete[] data;
    size = 0;
}