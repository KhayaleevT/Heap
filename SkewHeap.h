//
// Created by maent on 14.12.2019.
//

#ifndef UNTITLED_SKEWHEAP_H
#define UNTITLED_SKEWHEAP_H

#include "IHeap.h"


template<typename T>
class SkewHeap : public IHeap<T> {
private:
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

    };

    Vertex *root = nullptr;

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
        std::swap(root1->left, root1->right);
        return root1;
    }

public:
    void Merge(IHeap<T> &b1) {
        SkewHeap<T> &b = dynamic_cast<SkewHeap<T> &>(b1);
        root = Meld(root, b.root);
        b.root = nullptr;
    }

    T GetMin() {
        return root->value;
    }

    void ExtractMin() {
        Vertex *l = root->left;
        Vertex *r = root->right;
        delete root;
        root = Meld(l, r);
    }

    void Insert(T x) {
        SkewHeap *a = new SkewHeap(x);
        Merge(*a);
    }

    SkewHeap(SkewHeap &) = delete;

    SkewHeap() = default;

    explicit SkewHeap(T x) {
        root = new Vertex(x);
    }

    SkewHeap &operator=(SkewHeap &) = delete;

    ~SkewHeap() {
        if (root != nullptr)root->_destruct();
    }

    bool Empty() {
        return root == nullptr;
    }
};

#endif //UNTITLED_SKEWHEAP_H
