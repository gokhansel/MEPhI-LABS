#pragma once

#include <vector>
#include "Heap.hpp"

template<class T>
class Iterator {

public:
    int index;
    vector<pair<Node<T> *, bool>> queue;


    explicit Iterator(Node<T> *c) {
        queue.push_back(make_pair(c, true));
        index = 0;
    }

    T &getCurrent() const {
        return queue[index].first->value;
    }

    void setCurrent(T &item) {
        queue[index].first->value = item;
    }

    [[nodiscard]] int getIndex() const {
        return index;
    }

    bool hasNext() const {
        if ((index < queue.size() - 1) or ((queue[index].second) and ((queue[index].first->left) or (queue[index].first->right)))) {
            return true;
        } else {
            return false;
        }
    }

    bool hasPrev() const {
        if (index > 0) {
            return true;
        } else {
            return false;
        }
    }

    Iterator<T> &operator++() {
        if (queue[index].second) {
            if (queue[index].first->left)
                queue.insert(queue.begin() + index + 1, 1, make_pair(queue[index].first->left, true));
            if (queue[index].first->right)
                queue.insert(queue.begin() + index + 1, 1, make_pair(queue[index].first->right, true));
            queue[index].second = false;
        }
        if (hasNext())
            index++;
        return *this;
    }

    Iterator<T> &operator--() {
        if (hasPrev())
            index--;
        return *this;
    }

    Iterator<T> *operator++(int) {
        ++(*this);
        return this;
    }

    Iterator<T> *operator--(int) {
        --(*this);
        return this;
    }
};