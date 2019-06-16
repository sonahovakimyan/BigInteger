//
//  main.cpp
//

#include "BigInteger.h"

#include <iostream>

int main(int argc, const char * argv[]) {
   
    BigInteger a("0000024325", NumberType::Positive);
    BigInteger b("0000024325", NumberType::Positive);
    std::cout <<  (a < b) << std::endl;
    std::cout <<  (a > b) << std::endl;
    std::cout <<  (a == b) << std::endl;
    
    auto add = a + b;
    auto sub = a - b;
    auto mul = a * b;
    auto div = a / b;
    std::cout <<  add.toString() << std::endl;
    std::cout <<  sub.toString() << std::endl;
    std::cout <<  mul.toString() << std::endl;
    std::cout <<  div.toString() << std::endl;
    return 0;
}
