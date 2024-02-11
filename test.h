#ifndef GOST_R_34_11_94_TEST_H
#define GOST_R_34_11_94_TEST_H

#include "iostream"
#include "hash.h"
#include "Utils.h"

void test(){
    ///
    /// std::vector<bool> stringToBinaryVector(const std::string& str)
    ///
    std::cout << "std::vector<bool> stringToBinaryVector(const std::string& str):" << std::endl;
    std::string str = "ABC 01";
    std::vector<bool> vecBin = stringToBinaryVector(str);
    std::cout << str << std::endl;
    for (int i = 0; i < vecBin.size(); i++){
        if ((i % 8 == 0) & (i != 0)) std::cout << " ";
        std::cout << vecBin[i];
    }
    std::cout << std::endl << std::endl;


    ///
    /// int fi(int n)
    ///
    std::cout << "int fi(int n):" << std::endl;
    bool check = true;
    for (int i = 0; i < 32; i++){
        std::cout << i << " = " << fi(i) << std::endl;
        (fi(i) >= 32) || (fi(i) < 0) ? check = false : 0;
    }
    if (check) std::cout << "int fi(int n) passed.";
    std::cout << std::endl << std::endl;


    ///
    /// int hexCharToDecimal(char c)
    ///
    std::cout << "int hexCharToDecimal(char c):" << std::endl;
    for (int i = '0'; i <= '9'; i++){
        std::cout << (char)i << " = " << hexCharToDecimal(i) << std::endl;
    }
    std::cout << 'A' << " = " << hexCharToDecimal('A') << std::endl;
    std::cout << 'B' << " = " << hexCharToDecimal('B') << std::endl;
    std::cout << 'C' << " = " << hexCharToDecimal('C') << std::endl;
    std::cout << 'D' << " = " << hexCharToDecimal('D') << std::endl;
    std::cout << 'E' << " = " << hexCharToDecimal('E') << std::endl;
    std::cout << 'F' << " = " << hexCharToDecimal('F') << std::endl;


    ///
    /// std::vector<bool> hexStrToBinaryVector(const std::string& inputH, bool isTest)
    ///
    std::cout << "std::vector<bool> hexStrToBinaryVector(const std::string& inputH, bool isTest):" << std::endl;
    std::vector<bool> a = hexStrToBinaryVector("AA0F", true);
    std::vector<bool> b({true, false, true, false, true, false, true, false,false,false,false,false,true,true,true,true});
    for (int i = 0; i < a.size(); i++) std::cout << (a[i] ? '1' : '0');
    std::cout << std::endl;
    for (int i = 0; i < b.size(); i++) std::cout << (b[i] ? '1' : '0');
    std::cout << std::endl;
    if (a == b) std::cout << "Test passed.";
    else std::cout << "Test ruined.";
    std::cout << std::endl << std::endl;

    ///
    /// std::vector<bool> xor_func(std::vector<bool> a, std::vector<bool> b)
    ///
    std::cout << "std::vector<bool> xor_func(std::vector<bool> a, std::vector<bool> b):" << std::endl;
    std::vector<bool> c = xor_func(std::vector<bool>({false, false, true, false}),
                                   std::vector<bool>({true, false, true, true}));
    std::vector<bool> d({true, false, false, true});
    std::cout << (c == d? "Test passed." : "Test ruined.");
    std::cout << std::endl;
}



#endif //GOST_R_34_11_94_TEST_H
