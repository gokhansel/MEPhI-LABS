#pragma once

#include "Sequences.h"

template<typename T>
bool cmp1(const T &a, const T &b) {
    return a <= b;
}

template<typename T>
bool cmp2(const T &a, const T &b) {
    return a < b;
}

template<typename T>
bool cmp3(const T &a, const T &b) {
    return a > b;
}

template<typename T>
bool cmp4(const T &a, const T &b) {
    return a >= b;
}

template<typename T>
void IsOk(Sequence<T>* seq,bool(*cmp)(const T &, const T &)){
    for (int i = 0; i < seq->GetLength() - 1; ++i) {
        if(!cmp(seq->Get(i),seq->Get(i + 1))){
            std::cout << "Error" << std::endl;
            exit(0);
        }
    }
    std::cout << "TEST PASSED" << std::endl;
}