#ifndef GOST_R_34_11_94_TEST_H
#define GOST_R_34_11_94_TEST_H

#include "iostream"
#include "hash.h"
#include "Utils.h"

void test(){
    std::cout << "std::vector<bool> stringToBinaryVector(const std::string& str):" << std::endl;
    std::string str = "ABC 01";
    std::vector<bool> vecBin = stringToBinaryVector(str);
    std::cout << str << std::endl;
    for (int i = 0; i < vecBin.size(); i++){
        if ((i % 8 == 0) & (i != 0)) std::cout << " ";
        std::cout << vecBin[i];
    }
    std::cout << std::endl;
}

#endif //GOST_R_34_11_94_TEST_H
