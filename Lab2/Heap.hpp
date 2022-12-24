#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

template<class T>
class Node {
public:
    T value;
    Node<T> *parent = nullptr;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;

    bool (*cmp)(const T &, const T &);

    Node(T value1, Node<T> *parent1, Node<T> *left1, Node<T> *right1, bool (*cmp)(const T &, const T &)) : value(value1), parent(parent1), left(left1), right(right1), cmp(cmp) {}

    /// Поиск элемента
    Node *search(T target) {
        if (target == value)
            return this;
        if (left) {
            if (target == left->value)
                return left;
            if (cmp(left->value, target)) {
                auto searched = left->search(target);
                if (searched) return searched;
            }
        }
        if (right) {
            if (target == right->value)
                return right;
            if (cmp(right->value, target)) {
                auto searched = right->search(target);
                return searched;
            }
        }
        return nullptr;
    }

    /// Вставка элемента
    void insert(T target) {
        if (!left) {
            left = new Node<T>(target, this, nullptr, nullptr, cmp);
            if (right && (cmp(left->value, right->value))) swap(left, right);
            return;
        }
        if (cmp(left->value, target)) {
            left->insert(target);
            return;
        }
        if (!right) {
            right = new Node<T>(target, this, nullptr, nullptr, cmp);
            if (left && (cmp(left->value, right->value))) swap(left, right);
            return;
        }
        if (cmp(right->value, target)) {
            right->insert(target);
            return;
        }
        Node *new_node = new Node<T>(target, this, right, nullptr, cmp);
        right->parent = new_node;
        right = new_node;
        if (cmp(left->value, right->value)) swap(left, right);
    }

    void print(ostream &out) {
        out << value;
        out << " ";
        if (right) right->print(out);
        if (left) left->print(out);
    }

    /// Получить вектор значений
    void getValues(vector<T> &values) {
        values.push_back(value);
        if (right) right->getValues(values);
        if (left) left->getValues(values);
    }

    ~Node() {
        if (parent) {
            if (parent->left && parent->left == this) parent->left = nullptr;
            if (parent->right && parent->right == this) parent->right = nullptr;
            parent = nullptr;
        }
        parent = nullptr;
        if (left) {
            if (left->parent == this) left->parent = nullptr;
            left = nullptr;
        }
        if (right) {
            if (right->parent == this) right->parent = nullptr;
            right = nullptr;
        }
    }
};

template<class T>
class Heap {
public:
    Node<T> *root = nullptr;

    bool (*cmp)(const T &, const T &);

    /// пустой Heap
    explicit Heap(bool (*cmp)(const T &, const T &)) : root(nullptr), cmp(cmp) {}

    /// Heap из array
    explicit Heap(const T *list, int size, bool (*cmp)(const T &, const T &)) : cmp(cmp) {
        for (int i = 0; i < size; i++) {
            insert(list[i]);
        }
    }

    /// Heap из vector
    explicit Heap(const vector<T> &vec, bool (*cmp)(const T &, const T &)) : cmp(cmp) {
        for (T item: vec) {
            insert(item);
        }
    }

    /// Копирующий конструктор
    Heap(const Heap<T> &heap) {
        if (heap.root) {
            root = new Node<T>(heap.root->value, heap.root->parent, heap.root->left, heap.root->right);
            if (root->left)
                copyChild(*(heap.root->left), *root, 1);
            if (root->right)
                copyChild(*(heap.root->right), *root, 0);
        }
        cmp = heap.cmp;
    }

    /// Копировать наследников
    void copyChild(Node<T> &item, Node<T> &p, int if_left) const {
        auto *node = new Node<T>(item.value, &p, nullptr, nullptr, cmp);
        if (item.left) node->left = item.left;
        if (item.right) node->right = item.right;
        if (if_left)
            p.left = node;
        else
            p.right = node;
        if (node->left)
            copyChild(*(item.left), *node, 1);
        if (node->right)
            copyChild(*(item.right), *node, 0);
    }

    /// Поиск элемента
    [[nodiscard]] bool search(const T &target) const {
        if (root && root->search(target)) return true;
        return false;
    }

    /// Вставка элемента
    void insert(const T &target) {
        if (!root) {
            root = new Node<T>(target, nullptr, nullptr, nullptr, cmp);
            return;
        }

        if (cmp(root->value, target)) {
            if (!search(target))
                root->insert(target);
        } else {
            auto *new_node = new Node<T>(target, nullptr, root, nullptr, cmp);
            root->parent = new_node;
            root = new_node;
        }
    }

    /// Удаление элемента
    void remove(const T &target) {
        if (!root) return;
        if (cmp(target, root->value)) return;
        Node<T> *node = root->search(target);
        if (!node)
            return;
        while (node->left && node->right) {
            if (cmp(node->left->value, node->right->value)) swap(node->left, node->right);
            swap(node->value, node->right->value);
            node = node->right;
        }
        if (node->parent) {
            if (node->left) {
                if (node->parent->right && node->parent->right == node) {
                    node->parent->right = node->left;
                    node->left->parent = node->parent;
                }
                if (node->parent->left && node->parent->left == node) {
                    node->parent->left = node->left;
                    node->left->parent = node->parent;
                }
            }
            if (node->right) {
                if (node->parent->right && node->parent->right == node) {
                    node->parent->right = node->right;
                    node->right->parent = node->parent;
                }
                if (node->parent->left && node->parent->left == node) {
                    node->parent->left = node->right;
                    node->right->parent = node->parent;
                }
            }
        } else {
            if (!node->left && !node->right) {
                root = nullptr;
            }
            if (node->left) {
                root = node->left;
            }
            if (node->right) {
                root = node->right;
            }
        }
        delete node;
    }

    /// Вывод
    void print(ostream &out) const {
        if (root) root->print(out);

    }

    /// Получить значения
    [[nodiscard]] vector<T> getValues() const {
        vector<T> vector;
        if (root) root->getValues(vector);
        return vector;
    }

    ~Heap() = default;
};