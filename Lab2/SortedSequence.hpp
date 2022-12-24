#pragma once

#include <vector>
#include "Heap.hpp"
#include "Iterator.hpp"

using namespace std;

template<class T>
class SortedSequence {
    int count = 0;
    Heap<T> *heap;
    Iterator<T> *iterator;

public:
    explicit SortedSequence(bool (*cmp)(const T &, const T &)) {
        heap = new Heap<T>(cmp);
    }

    explicit SortedSequence(const vector<T> &vec, bool (*cmp)(const T &, const T &)) {
        heap = new Heap<T>(cmp);
        for (T item: vec) {
            add(item);
        }
    }

    void add(T element) {
        heap->insert(element);
        count++;
        iterator = new Iterator<T>(heap->root);
    }

    void remove(T element) {
        if (search(element)) {
            heap->remove(element);
            count--;
        }
        if (count > 0)
            iterator = new Iterator<T>(heap->root);
    }

    T get(int index) {
        if ((index < 0) or (index >= count))
            throw out_of_range("Index out of range");
        while (iterator->getIndex() < index)
            (*iterator)++;
        while (iterator->getIndex() > index)
            (*iterator)--;
        return iterator->getCurrent();
    }

    T getFirst() {
        return heap->root->value;
    }

    vector<T> getValues() {
        return heap->getValues();
    }

    int getCount() {
        return count;
    }

    bool search(T element) {
        return heap->search(element);
    }

};