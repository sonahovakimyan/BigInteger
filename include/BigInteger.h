//
//  BigInteger.h
//

#ifndef BigInteger_h
#define BigInteger_h

#include <stdio.h>
#include <vector>

enum class NumberType {
    Positive,
    Negative
};

class BigInteger {
public:
    BigInteger(const std::string& number, const NumberType type);
    BigInteger operator + (const BigInteger& other) const;
    BigInteger operator - (const BigInteger& other) const;
    BigInteger operator * (const BigInteger& other) const;
    BigInteger operator / (const BigInteger& other) const;
    bool operator == (const BigInteger& other) const;
    bool operator > (const BigInteger& other) const;
    bool operator < (const BigInteger& other) const;
    const std::string toString() const;
private:
    BigInteger(const std::vector<short>& number, const NumberType type);
    std::vector<short> add(const std::vector<short>& other) const;
    std::vector<short> sub(const std::vector<short>& other) const;
    std::vector<short> mul(const short& other) const;
    short div(const BigInteger& other) const;
    bool _lesser(const BigInteger& other) const;
    bool _greater(const BigInteger& other) const;
    
    std::vector<short> m_integer;
    NumberType m_type;
};

#endif /* BigInteger_h */
