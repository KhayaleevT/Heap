//
// Created by maent on 16.12.2019.
//

#ifndef HEAP_LEFTHEAP_H
#define HEAP_LEFTHEAP_H
//
// Created by maent on 14.12.2019.

#include "IHeap.h"

template<typename T>
struct Vertex {
    T value;
    Vertex *left = nullptr, *right = nullptr;

    Vertex(T x) {
        left = nullptr;
        right = nullptr;
        value = x;
    }

    void _destruct() {
        if (left != nullptr) {
            left->_destruct();
        }
        if (right != nullptr) {
            right->_destruct();
        }
        delete this;
    }

    virtual void invariant_maintenance() = 0;

    static Vertex *Meld(Vertex *root1, Vertex *root2) {
        if (root1 == nullptr) {
            return root2;
        }
        if (root2 == nullptr) {
            return root1;
        }
        if (root1->value > root2->value) {
            std::swap(root1, root2);
        }
        root1->right = Meld(root1->right, root2);
        root1->invariant_maintenance();
        return root1;
    }
};

template<typename T>
class LeftHeap : public IHeap<T> {
public:
    Vertex<T> *root = nullptr;
public:
    void Merge(IHeap<T> &b1) {
        LeftHeap<T> &b = dynamic_cast<LeftHeap<T> &>(b1);
        root = Vertex<T>::Meld(root, b.root);
        b.root = nullptr;
    }

    T GetMin() {
        return root->value;
    }

    void ExtractMin() {
        Vertex<T> *l = root->left;
        Vertex<T> *r = root->right;
        delete root;
        root = Vertex<T>::Meld(l, r);
    }

    virtual void Insert(T x) {};

    LeftHeap(LeftHeap &) = delete;

    LeftHeap() = default;

    explicit LeftHeap(T x) {
        root = new Vertex<T>(x);
    }

    LeftHeap &operator=(LeftHeap &) = delete;

    ~LeftHeap() {
        if (root != nullptr)root->_destruct();
    }

    bool Empty() {
        return root == nullptr;
    }
};

#endif //HEAP_LEFTHEAP_H
