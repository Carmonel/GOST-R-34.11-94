#include <cstdint>
#include "hash.h"
#include "vector"
#include <cmath>

#include "Utils.h"

std::vector<bool> f_E(std::vector<bool> a, std::vector<bool> x){
    /// Перевод в 10-ричную
    uint64_t A, X;
    for (int i = 0; i < a.size(); i++){
        A = a[i] * pow(2, i);
        X = x[i] * pow(2, i);
    }

    /// Сложение в 10-ричной системе
    A = A % (uint64_t)pow(2, 32);
    X = X % (uint64_t)pow(2, 32);
    uint64_t res = A + X;

    /// Перевод в вектор
    std::vector<bool> G;
    while (res){
        G.insert(G.end(), X % 1);
        res >>= 1;
    }

    /// Разделение вектора + применение S_box
    std::vector<std::vector<bool>> g = splitVector(G, 8);
    for (int i = 0; i < g.size(); i++){
        char g_int = 0;
        for (int k = 0; k < g[i].size(); k++) g_int += pow(2, g[i].size() - k - 1);
        char g_new = S_box[i][g_int];

        std::vector<bool> S_box_bin;
        while (g_new){
            S_box_bin.insert(S_box_bin.begin(), g_new & 1);
            g_new >>= 1;
        }
        g[i] = S_box_bin;
    }

    /// Слияние + сдвиг на 11 влево
    std::vector<bool> result;
    for (int i = 0; i < g.size(); i++){
        result.insert(result.end(), g[i].begin(), g[i].end());
    }
    result.insert(result.end(), 11, false);

    G.clear();
    S_box.clear();
    return result;
}

std::vector<bool> E(std::vector<bool> M, std::vector<bool> K){
    /// Подключи из ключа
    std::vector<std::vector<bool>> m = splitVector(M, 2);
    std::vector<std::vector<bool>> k = splitVector(K, 8);
    std::vector<std::vector<bool>> x = k;
    x.insert(x.end(), x.begin(), x.end());
    x.insert(x.end(), x.begin(), x.begin() + 7);
    x.insert(x.end(), x.end(), x.begin());

    /// 32 раунда
    std::vector<bool> A, B;
    A = m[1];
    B = m[2];
    for (int i = 0; i < 32; i++){
        A = xor_func(B, f_E(A, x[i]));
        B = A;
    }

    /// Слияние в результат
    std::vector<bool> result = A;
    result.insert(result.end(), B.begin(), B.end());

    A.clear();
    B.clear();
    m.clear();
    k.clear();
    x.clear();
    return result;
}

std::vector<bool> P(std::vector<bool> V){
    std::vector<std::vector<bool>> v = splitVector(V, 8);

    std::vector<bool> result;
    for (int i = 31; i >= 0; i--){
        int tmp = eulerPhi(i);
        result.insert(result.begin(), v[tmp].begin(), v[tmp].end());
    }

    v.clear();
    return result;
}

std::vector<bool> A(std::vector<bool> V){
    std::vector<std::vector<bool>> v;
    v.emplace_back(V.begin(), V.begin() + 63);
    v.emplace_back(V.begin() + 64, V.begin() + 127);
    v.emplace_back(V.begin() + 128, V.begin() + 191);
    v.emplace_back(V.begin() + 192, V.end());

    std::vector<bool> result = xor_func(v[0], v[1]);
    for (int i = 3; i >= 1; i--) result.insert(result.end(), v[i].begin(), v[i].end());

    v.clear();
    return result;
}

std::vector<bool> phi(std::vector<bool> V){
    std::vector<std::vector<bool>> v = splitVector(V, 16);

    std::vector<bool> result = xor_func(v[1], v[2]);
    result = xor_func(result, v[3]);
    result = xor_func(result, v[4]);
    result = xor_func(result, v[13]);
    result = xor_func(result, v[16]);

    for (int i = 15; i >= 1; i--){
        result.insert(result.end(), v[i].begin(), v[i].end());
    }

    v.clear();
    return result;
}

std::vector<bool> f(std::vector<bool> H_in, std::vector<bool> m){
    /// Генерация ключей
    std::vector<std::vector<bool>> K;
    std::vector<bool> U = H_in;
    std::vector<bool> V = m;
    std::vector<bool> W = xor_func(H_in, m);
    K.push_back(P(W));

    for (int j = 2; j < 5; j++){
        U = xor_func(A(U), C[j]);
        V = A(A(V));
        W = xor_func(U, V);
        K.push_back(P(W));
    }

    /// Шифруююще преобразование
    std::vector<std::vector<bool>> h = splitVector(H_in, 64);

    std::vector<std::vector<bool>> s;
    for (int i = 0; i < 4; i++) s.push_back(E(h[i], K[i]));

    std::vector<bool> S(s[0]);
    for (int i = 1; i < 4; i++) S.insert(S.begin(), s[i].begin(), s[i].end());

    /// Перемешивающее преобразование
    std::vector<bool> H_out = S;
    for (int i = 0; i < 12; i++) H_out = phi(H_out);
    H_out = xor_func(m, H_out);
    H_out = phi(H_out);
    H_out = xor_func(H_in, H_out);
    for (int i = 0; i < 61; i++) H_out = phi(H_out);

    U.clear();
    V.clear();
    W.clear();
    K.clear();
    s.clear();
    S.clear();
    return H_out;
}

void hash(const std::string& str, const std::string& inputH){
    generate_C();

    std::vector<bool> m = stringToBinaryVector(str);
    std::vector<bool> H1 = hexStrToBinaryVector(inputH);

    std::vector<bool> h = H1; // значение хэш-функции
    std::vector<bool> K(256, false); // контрольная сумма
    int L = 0; // длина сообщения
    int pos = 0;

    while (m.size() - pos > 256){
        std::vector<bool> m_i = std::vector<bool>(m.begin() + pos, m.begin() + pos + BLOCK_SIZE);
        h = f(h, m_i);
        L = L + 256;
        K = vectorSum(K, m_i);
    }

    std::vector<bool> m_n = std::vector<bool>(m.begin() + pos, m.end());
    L = L + m_n.size();
    m_n = addZerosToBegin(m_n);
    K = vectorSum(K, m_n);
    h = f(h, m_n);
    h = f(h, L);
    h = f(h, K);
}
