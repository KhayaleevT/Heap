//
// Created by maent on 16.12.2019.
//

#ifndef HEAP_LEFTHEAP_H
#define HEAP_LEFTHEAP_H
//
// Created by maent on 14.12.2019.

#include "IHeap.h"

template<typename T>
struct VertexLeft : Vertex<T> {
    using Vertex<T>::Vertex;

    virtual void invariant_maintenance() = 0;

    static Vertex<T> *Meld(Vertex<T> *root1, Vertex<T> *root2) {
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
        VertexLeft<T> *r1 = dynamic_cast<VertexLeft<T> *>(root1);
        r1->invariant_maintenance();
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
        root = VertexLeft<T>::Meld(root, b.root);
        b.root = nullptr;
    }

    T GetMin() {
        return root->value;
    }

    void ExtractMin() {
        Vertex<T> *l = root->left;
        Vertex<T> *r = root->right;
        root->Make_Empty();
        delete root;
        root = VertexLeft<T>::Meld(l, r);
    }

    virtual void Insert(T x) = 0;

    LeftHeap(LeftHeap &) = delete;

    LeftHeap() = default;

    explicit LeftHeap(T x) {
        root = new VertexLeft<T>(x);
    }

    LeftHeap &operator=(LeftHeap &) = delete;

    ~LeftHeap() {
        delete root;
    }

    bool Empty() {
        return root == nullptr;
    }
};

#endif //HEAP_LEFTHEAP_H
