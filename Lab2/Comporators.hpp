#pragma once

#include "Person.hpp"

template<class T>
bool Less(const T &a, const T &b) {
    return a < b;
}

template<class T>
bool Greater(const T &a, const T &b) {
    return a > b;
}

bool PersonLess(const Person &a, const Person &b) {
    if (a.name != b.name) {
        return a.name < b.name;
    }
    if (a.country != b.country) {
        return a.country < b.country;
    }
    if (a.age != b.age) {
        return a.age < b.age;
    }
    return false;
}

bool PersonGreater(const Person &a, const Person &b) {
    if (a.name != b.name) {
        return a.name > b.name;
    }
    if (a.country != b.country) {
        return a.country > b.country;
    }
    if (a.age != b.age) {
        return a.age > b.age;
    }
    return false;
}