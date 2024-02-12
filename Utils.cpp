#include "Utils.h"
#include "vector"
#include "string"
#include "iostream"

std::vector<bool> stringToBinaryVector(const std::string& str) {
    std::vector<bool> binaryStr;
    for (char c : str) {
        for (int i = 7; i >= 0; --i) {
            binaryStr.push_back((c >> i) & 1);
        }
    }

    return binaryStr;
}

int hexCharToDecimal(char c) {
    if (std::isdigit(c)) {
        return c - '0';
    } else {
        return std::tolower(c) - 'a' + 10; // Преобразуем заглавные буквы в строчные и вычитаем 'a' + 10
    }
}

// Функция, которая проверяет, является ли символ шестнадцатеричной цифрой
bool isHexDigit(char c) {
    return (std::isdigit(c) || (std::tolower(c) >= 'a' && std::tolower(c) <= 'f'));
}

std::vector<bool> hexStrToBinaryVector(const std::string& inputH, bool isTest){
    if (!isTest){
        if (inputH.length() != 64){
            std::cerr << "H1 length != 64!";
            exit(-1);
        }
    }

    for (char c : inputH) {
        if (!isHexDigit(c)) {
            std::cerr << "Input H1 not a hex!";
            exit(-1);
        }
    }

    std::vector<bool> binaryVector;
    binaryVector.reserve(inputH.size() * 4);

    for (char c : inputH) {
        int decimalValue = hexCharToDecimal(c);
        for (int i = 3; i >= 0; --i) {
            binaryVector.push_back((decimalValue >> i) & 1);
        }
    }

    return binaryVector;
}

std::vector<bool> xor_func(std::vector<bool> a, std::vector<bool> b){
    if (a.size() != b.size()){
        std::cerr << "xor_func: sizes not equals!";
        exit(-1);
    }

    std::vector<bool> result;
    result.reserve(a.size());
    for (int i = 0; i < a.size(); i++){
        result.push_back(a[i] ^ b[i]);
    }

    return result;
}

std::vector<bool> vectorSum(std::vector<bool> a, std::vector<bool> b){
    std::vector<bool> result;
    bool carry = false;

    int i = a.size() - 1;
    int j = b.size() - 1;
    int k = 0;
    while (i >= 0 || j >= 0 || carry) {
        // Получаем текущие биты из векторов, если они еще не закончились
        bool bitA = (i >= 0) && a[i];
        bool bitB = j >= 0 && b[j];

        // Вычисляем сумму текущих битов и остатка
        bool sum = bitA ^ bitB ^ carry;

        // Обновляем остаток для следующей итерации
        carry = (bitA & bitB) | (bitA & carry) | (bitB & carry);

        // Добавляем текущий бит к результату
        result.insert(result.begin(), sum);

        // Переходим к предыдущим битам
        i--;
        j--;
    }

    return result;
}

std::vector<std::vector<bool>> splitVector(std::vector<bool> V, int splitsCount){
    std::vector<std::vector<bool>> v;
    for (int pos = 0; pos < BLOCK_SIZE / splitsCount; pos++){
        v.emplace_back(V.begin() + (splitsCount * pos), V.begin() + (splitsCount * pos + splitsCount - 1));
    }

    return v;
}

void generate_C(){
    C.emplace_back(256, false);
    C.emplace_back(256, false);

    std::string c_tmp = "ff00ffff000000ffff0000ff00ffff0000ff00ff00ff00ffff00ff00ff00ff00";
    std::vector<bool> c_tmp_vec;
    c_tmp_vec.reserve(256);
    for (int i = 0; i < c_tmp.size(); i++){
        if (c_tmp[i] == 'f'){
            c_tmp_vec.push_back(true);
            c_tmp_vec.push_back(true);
            c_tmp_vec.push_back(true);
            c_tmp_vec.push_back(true);
            continue;
        }
        if (c_tmp[i] == '0'){
            c_tmp_vec.push_back(false);
            c_tmp_vec.push_back(false);
            c_tmp_vec.push_back(false);
            c_tmp_vec.push_back(false);
        }
    }
    C.emplace_back(c_tmp_vec);

    C.emplace_back(256, false);
}

int fi(int n) {
    int i = n & 0x03;
    int k = n >> 2;
    k++;
    return (i << 3) + k - 1;
}

std::vector<bool> addZerosToBegin(std::vector<bool> v){
    while (v.size() != 256) v.insert(v.begin(), false);
    return v;
}