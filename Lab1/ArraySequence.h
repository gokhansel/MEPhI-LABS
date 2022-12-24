#pragma once

#include "Sequences.h"
#include "ISorter.h"

template<typename T>
class ArraySequence : public Sequence<T> {
public:


    ArraySequence() : data() {}

    ArraySequence(int count) : data(count) {}

    ArraySequence(T *item, int count) : data(item, count) {}

    ArraySequence(ArraySequence<T> &array) : data(array.data) {}

    ArraySequence(LinkedList<T> &list) {
        T *items;
        items = (T *) malloc(sizeof(T) * (list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }
        data = DynamicArray<T>(items, list.GetLength());
    }

    int GetLength() {
        return data.GetSize();
    }

    T &Get(int index) {
        return data.Get(index);
    }

    T &GetFirst() {
        return data.Get(0);
    }

    T &GetLast() {
        return data.Get(data.GetSize() - 1);
    }

    void Append(T item) {
        data.Append(item);
    }

    void Prepend(T item) {
        data.Prepend(item);
    }

    void InsertAt(T item, int index) {
        if (index >= data.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        data.Resize(data.GetSize() + 1);
        for (int i = data.GetSize() - 2; i >= index; --i) {
            data.Set(i + 1, data.Get(i));
        }
        data.Set(index, item);
    }

    void Print() {
        data.Print();
    }

    void BubbleSort(bool(*cmp)(const T &, const T &)) override {
        IBubbleSort<T> sort;
        sort.Sort(cmp,this);
    }

    void ShellSort(bool(*cmp)(const T &, const T &)) override {
        IShellSort<T> sort;
        sort.Sort(cmp, this);
    }

    void BinaryInsertSort(bool(*cmp1)(const T &, const T &),bool(*cmp2)(const T &, const T &)) override {
        IBinaryInsertSort<T> sort;
        sort.Sort(cmp1,this,cmp2);
    }

private:
    DynamicArray<T> data;

};