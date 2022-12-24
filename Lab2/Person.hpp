#pragma once

#include <string>
#include <iostream>
#include <random>
#include <fstream>

using namespace std;

struct Person {
    string name;
    string country;
    int age;
};

ostream &operator<<(ostream &os, const Person &p) {
    os << "{" << p.name << ", " << p.country << ", " << p.age << "}";
    return os;
}

bool operator==(const Person &a, const Person &b) {
    if ((a.name == b.name) and (a.country == b.country) and (a.age == b.age))
        return true;
    return false;
}

vector<string> names = {"Anastasia", "Maksim", "Svetlana", "Aleksey", "Olga", "Aleksandr", "Alisa", "Dmitriy", "Varvara", "Matvey", "Zoya", "Oleg", "Larisa", "Semyon", "Oksana", "Yaroslav", "Margarita", "Nikolay", "Maya", "Vladimir", "Polina", "Grigoriy"};

vector<string> countries = {"Russia", "Albania", "Belarus", "Germany", "Egypt", "Japan", "Mexico", "Korea", "Brazil", "Canada", "USA", "Luxembourg"};

Person getRandomPerson() {
    Person p;
    p.name = names[rand() % names.size()];
    p.country = countries[rand() % countries.size()];
    p.age = rand() % 90 + 10;
    return p;
}

Person getFromStream(istream &is) {
    Person p;
    int age;
    string name, country;
    is >> name >> country >> age;
    p.name = name;
    p.country = country;
    p.age = age;
    return p;
}

vector<Person> getFromTXT(const string &path) {
    int n, age;
    string name, country;
    vector<Person> persons;

    ifstream fin(path);
    if (fin.is_open()) {
        fin >> n;
        for (int i = 0; i < n; i++) {
            auto p = getFromStream(fin);
            persons.push_back(p);
        }
    }
    fin.close();
    return persons;
}

void putInTXT(const vector<Person> &persons, const string &path) {
    ofstream fout(path);
    if (fout.is_open()) {
        for (int i = 0; i < persons.size(); i++) {
            fout << i << endl;
            fout << persons[i].name << endl;
            fout << persons[i].country << endl;
            fout << persons[i].age << endl;
        }
    }
    fout.close();
}