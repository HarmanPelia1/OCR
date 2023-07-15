// Copy in your bigint.h (overwrite this file)
//  and then add the appropriate code
#ifndef BIGINT_H
#define BIGINT_H
#include <string>
#include <vector>

class BigInt {
public:
    BigInt(std::string s, int base=10); // convert string to BigInt
    std::string to_string() const; // get string representation
    void add(BigInt b); // add another BigInt to this one


    BigInt operator+(const BigInt& rhs) const;//Similar to add function
    BigInt operator-(const BigInt& rhs) const;
    bool operator<(const BigInt& rhs) const; 
private:
    // whatever you need
    int new_base;
    std::vector<int> numbers;
    void removeLeadingZeroes();

};

#endif