#pragma once

#include <cassert>
#include <random>
#include <string>
#include "SortedSequence.hpp"
#include "Comporators.hpp"
#include "Person.hpp"

#define Max 1e6

default_random_engine generator;
uniform_int_distribution<int> distribution(-Max, Max);

void test_less() {
    int a = distribution(generator);
    int b = distribution(generator);

    assert((a < b) == Less(a, b));
}

void test_greater() {
    int a = distribution(generator);
    int b = distribution(generator);

    assert((a > b) == Greater(a, b));
}

void test_person_less() {
    Person a;
    a.name = "A";
    a.country = "A";
    a.age = 10;
    Person b;
    b.name = "B";
    b.country = "B";
    b.age = 20;

    assert(PersonLess(a, b) == true);
    assert(PersonLess(b, a) == false);
}

void test_person_greater() {
    Person a;
    a.name = "A";
    a.country = "A";
    a.age = 10;
    Person b;
    b.name = "B";
    b.country = "B";
    b.age = 20;

    assert(PersonGreater(a, b) == false);
    assert(PersonGreater(b, a) == true);
}

void test_person_equal() {
    Person a;
    a.name = "A";
    a.country = "A";
    a.age = 10;
    Person b;
    b.name = "A";
    b.country = "A";
    b.age = 10;

    assert(a == b);
}


void test_sequence_add_get(const int n = 1e3) {
    vector<int> values(n);
    SortedSequence<int> seq(Less);
    for (int i = 0; i < n; i++) {
        int value = distribution(generator);
        values[i] = value;
        seq.add(value);
    }

    sort(values.begin(), values.end());

    for (int i = 0; i < n; i++) {
        assert(seq.get(i) == values[i]);
    }
}

void test_sequence_create(const int n = 1e3) {
    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        int value = distribution(generator);
        values[i] = value;
    }

    SortedSequence<int> seq(values, Less);
    sort(values.begin(), values.end());

    for (int i = 0; i < n; i++) {
        assert(seq.get(i) == values[i]);
    }
}

void test_sequence_remove(const int n = 1e3) {
    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        int value = distribution(generator);
        values[i] = value;
    }

    SortedSequence<int> seq(values, Less);

    for (int i = 0; i < n; i++) {
        seq.remove(values[i]);
    }
    assert(seq.getCount() == 0);
}

void test_sequence_search(const int n = 1e3) {
    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        int value = distribution(generator);
        values[i] = value;
    }

    SortedSequence<int> seq(values, Less);

    for (int i = 0; i < n; i++) {
        assert(seq.search(values[i]) == true);
    }
}