//
//  BigInteger.cpp
//

#include "BigInteger.h"

#include <iostream>
#include <string>
#include <sstream>

namespace {
    std::vector<short> stringToVector(const std::string& number) {
        std::vector<short>  result;
        for(const auto& i : number){
            result.push_back(i - '0');
        }
        return result;
    }
} // unnamed namespace

BigInteger::BigInteger(const std::string& number, NumberType type)
: BigInteger::BigInteger(stringToVector(number), type) {
}

BigInteger::BigInteger(const std::vector<short>& number, NumberType type)
    : m_type(type) {
        auto it = number.begin();
        while(*it == 0 && it != number.end()) {
            ++it;
        }
        
        while(it != number.end()) {
            m_integer.push_back(*it);
            ++it;
        }
        
        if(m_integer.empty()){
            m_type = NumberType::Positive;
            m_integer = {0};
        }
    }

BigInteger BigInteger::operator + (const BigInteger& other) const {
    if(m_type == NumberType::Negative) {
        if(other.m_type == NumberType::Negative) {
            return BigInteger(add(other.m_integer), NumberType::Negative);
        } else {
            if(_lesser(other)) {
                return BigInteger(other.sub(m_integer), NumberType::Positive);
            } else {
                return BigInteger(sub(other.m_integer), NumberType::Negative);
            }
        }
    } else {
        if(other.m_type == NumberType::Positive) {
            return BigInteger(add(other.m_integer), NumberType::Positive);
        } else {
            if(_greater(other)) {
                return BigInteger(sub(other.m_integer), NumberType::Positive);
            } else {
                return BigInteger(other.sub(m_integer), NumberType::Negative);
            }
        }
    }
}

BigInteger BigInteger::operator - (const BigInteger& other) const {
    if(m_type == NumberType::Negative) {
        if(other.m_type == NumberType::Positive) {
            return BigInteger(add(other.m_integer), NumberType::Negative);
        } else {
            if(_lesser(other)) {
                return BigInteger(other.sub(m_integer), NumberType::Positive);
            } else {
                return BigInteger(sub(other.m_integer), NumberType::Negative);
            }
        }
    } else {
        if(other.m_type == NumberType::Negative) {
            return BigInteger(add(other.m_integer), NumberType::Positive);
        } else {
            if(_greater(other)) {
                return BigInteger(sub(other.m_integer), NumberType::Positive);
            } else {
                return BigInteger(other.sub(m_integer), NumberType::Negative);
            }
        }
    }
}

BigInteger BigInteger::operator * (const BigInteger& other) const {
    BigInteger result("0", NumberType::Positive);
    auto temp = *this;
    for(auto it = other.m_integer.rbegin(); it != other.m_integer.rend(); ++it) {
        result =  BigInteger(result.add(temp.mul(*it)), NumberType::Positive);
        temp.m_integer.push_back(0);
    }
    if(m_type != other.m_type) {
        result.m_type = NumberType::Negative;
    }
    return result;
}

BigInteger BigInteger::operator / (const BigInteger& other) const {
    std::vector<short> result;
    if(_lesser(other)) {
        result = {0};
    } else {
        std::vector<short> tempInt;
        size_t index = 0;
        while(index < m_integer.size()) {
            tempInt.push_back(m_integer[index]);
            auto temp = BigInteger(tempInt, NumberType::Positive);
            if(other._greater(temp)) {
                result.push_back(0);
            } else {
                auto div = temp.div(other);
                result.push_back(div);
                tempInt = temp.sub(other.mul(div));
            }
            ++index;
        }
        
    }
    if(m_type == other.m_type) {
        return BigInteger(result, NumberType::Positive);
    } else {
        return BigInteger(result, NumberType::Negative);
    }
    
}

bool BigInteger::operator == (const BigInteger& other) const {
    if(m_type != other.m_type){
        return false;
    }
    if(m_integer.size() != other.m_integer.size()) {
        return false;
    }
    
    for(size_t i  = 0; i < m_integer.size(); ++i) {
        if(m_integer[i] != other.m_integer[i]){
            return false;
        }
    }

    return true;
}

bool BigInteger::operator > (const BigInteger& other)  const {
    if(m_type == NumberType::Negative) {
        if(other.m_type == NumberType::Negative) {
            return _lesser(other);
        }
        return false;
    } else if(other.m_type == NumberType::Positive) {
        return _greater(other);
    }
    return true;
}

bool BigInteger::operator < (const BigInteger& other) const {
    if(m_type == NumberType::Negative) {
        if(other.m_type == NumberType::Negative) {
            return _greater(other);
        }
        return true;
    } else if(other.m_type == NumberType::Positive) {
        return _lesser(other);
    }
    return false;
}

const std::string BigInteger::toString() const {
    std::stringstream stream;
    if(m_type == NumberType::Negative){
        stream << '-';
    }
    for(const auto& el : m_integer) {
        stream << el;
    }
    return stream.str();
}

std::vector<short> BigInteger::add(const std::vector<short>& other) const {
    std::vector<short> result;
    int carry = 0;
    auto firstIt = m_integer.rbegin();
    auto secondIt = other.rbegin();
    
    while(firstIt != m_integer.rend() || secondIt != other.rend()) {
        
        int temp;
        
        if(firstIt == m_integer.rend()) {
            temp = *secondIt + carry;
            ++secondIt;
        } else if(secondIt == other.rend()) {
            temp = *firstIt + carry;
            ++firstIt;
        } else {
            temp = *firstIt + *secondIt + carry;
            ++firstIt;
            ++secondIt;
        }

        if(temp > 9) {
            temp = temp - 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(temp);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<short> BigInteger::sub(const std::vector<short>& other) const {
    std::vector<short> result;
    int carry = 0;
    auto firstIt = m_integer.rbegin();
    auto secondIt = other.rbegin();
    
    while(firstIt != m_integer.rend() || secondIt != other.rend()) {
        
        int temp;
        
        if(firstIt == m_integer.rend()) {
            temp = *secondIt - carry;
            ++secondIt;
        } else if(secondIt == other.rend()) {
            temp = *firstIt - carry;
            ++firstIt;
        } else {
            temp = *firstIt - *secondIt - carry;
            ++firstIt;
            ++secondIt;
        }
        
        if(temp < 0) {
            temp = temp + 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(temp);
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<short> BigInteger::mul(const short& other) const {
    std::vector<short> result;
    short temp = 1;
    for(auto it = m_integer.rbegin(); it != m_integer.rend(); ++it) {
        temp = temp / 10 + (*it) * other;
        result.push_back(temp % 10);
    }
    result.push_back(temp / 10);
    std::reverse(result.begin(), result.end());
    return result;
}

short BigInteger::div(const BigInteger& other) const {
    for(short i = 1; i < 10; ++i) {
        auto temp = BigInteger(other.mul(i), NumberType::Positive);
        if(this->_lesser(temp)) {
            return --i;
        }
    }
    return 0;
}

bool BigInteger::_lesser(const BigInteger& other) const {
    if(m_integer.size() < other.m_integer.size()) {
        return true;
    }
    if(m_integer.size() == other.m_integer.size()) {
        for(size_t i  = 0; i < m_integer.size(); ++i) {
            if(m_integer[i] > other.m_integer[i]) {
                return false;
            } else if(m_integer[i] < other.m_integer[i]) {
                return true;
            }
        }
    }
    return false;
}

bool BigInteger::_greater(const BigInteger& other) const {
    
    if(m_integer.size() > other.m_integer.size()) {
        return true;
    }
    if(m_integer.size() == other.m_integer.size()) {
        for(size_t i  = 0; i < m_integer.size(); ++i) {
            if(m_integer[i] < other.m_integer[i]) {
                return false;
            } else if(m_integer[i] > other.m_integer[i]) {
                return true;
            }
        }
    }
    return false;
}
