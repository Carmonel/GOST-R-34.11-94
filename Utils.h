#ifndef GOST_R_34_11_94_UTILS_H
#define GOST_R_34_11_94_UTILS_H

#include <vector>
#include <string>

inline std::vector<std::vector<char>> S_box = {
        {'4', 'A', '9', '2', 'D', '8', '0', 'E', '6', 'B', '1', 'C', '7', 'F', '5', '3'},
        {'E', 'B', '4', 'C', '6', 'D', 'F', 'A', '2', '3', '8', '1', '0', '7', '5', '9'},
        {'5', '8', '1', 'D', 'A', '3', '4', '2', 'E', 'F', 'C', '7', '6', '0', '9', 'B'},
        {'7', 'D', 'A', '1', '0', '8', '9', 'F', 'E', '4', '6', 'C', 'B', '2', '5', '3'},
        {'6', 'C', '7', '1', '5', 'F', 'D', '8', '4', 'A', '9', 'E', '0', '3', 'B', '2'},
        {'4', 'B', 'A', '0', '7', '2', '1', 'D', '3', '6', '8', '5', '9', 'C', 'F', 'E'},
        {'D', 'B', '4', '1', '3', 'F', '5', '9', '0', 'A', 'E', '7', '6', '8', '2', 'C'},
        {'1', 'F', 'D', '0', '5', '7', 'A', '4', '9', '2', '3', 'E', '6', 'B', '8', 'C'}
};

inline std::vector<std::vector<bool>> C;

const int BLOCK_SIZE = 256;

std::vector<bool> stringToBinaryVector(const std::string& str);
int hexCharToDecimal(char c);
bool isHexDigit(char c);
std::vector<bool> hexStrToBinaryVector(const std::string& inputH, bool isTest);
std::vector<bool> xor_func(std::vector<bool> a, std::vector<bool> b);
std::vector<bool> vectorSum(std::vector<bool> a, std::vector<bool> b);
std::vector<std::vector<bool>> splitVector(std::vector<bool> V, int splitsCount);
void generate_C();
int fi(int n);
std::vector<bool> addZerosToBegin(std::vector<bool> v);

#endif //GOST_R_34_11_94_UTILS_H
