#pragma once

#include "DynamicArray.h"
#include "LinkedList.h"

template<typename T>
class Sequence {
public:

    virtual T &GetFirst() = 0;

    virtual T &GetLast() = 0;

    virtual T &Get(int index) = 0;

    virtual void QuickSort(bool(*cmp)(const T &, const T &)) = 0;

    virtual void MergeSort(bool(*cmp)(const T &, const T &)) = 0;

    virtual void BinaryInsertSort(bool(*cmp1)(const T &, const T &),bool(*cmp2)(const T &, const T &)) = 0;

    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, int index) = 0;

    virtual void Print() = 0;
};


