//
// Created by maent on 14.12.2019.
//

#ifndef UNTITLED_LEFTISTHEAP_H
#define UNTITLED_LEFTISTHEAP_H

#include "IHeap.h"

template<typename T>
class LeftistHeap : public IHeap<T> {
private:
    struct Vertex {
        T value;
        int rank = 0;
        Vertex *left = nullptr, *right = nullptr;

        static int rk(Vertex *a) {
            if (a == nullptr) {
                return 0;
            } else return a->rank;
        }

        Vertex(T x) {
            left = nullptr;
            right = nullptr;
            value = x;
            rank = 1;
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
        if (Vertex::rk(root1->left) < Vertex::rk(root1->right)) {
            std::swap(root1->left, root1->right);
        }
        root1->rank = std::min(Vertex::rk(root1->left), Vertex::rk(root1->right)) + 1;
        return root1;
    }

public:
    void Merge(IHeap<T> &b1) {
        LeftistHeap<T> &b = dynamic_cast<LeftistHeap<T> &>(b1);
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
        LeftistHeap *a = new LeftistHeap(x);
        Merge(*a);
    }

    LeftistHeap(LeftistHeap &) = delete;

    LeftistHeap() = default;

    explicit LeftistHeap(T x) {
        root = new Vertex(x);
    }

    LeftistHeap &operator=(LeftistHeap &) = delete;

    ~LeftistHeap() {
        if (root != nullptr) {
            root->_destruct();
        }
    }

    bool Empty() {
        return root == nullptr;
    }
};

#endif //UNTITLED_LEFTISTHEAP_H
