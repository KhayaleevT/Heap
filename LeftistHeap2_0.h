//
// Created by maent on 16.12.2019.
//

#ifndef HEAP_LEFTISTHEAP2_0_H
#define HEAP_LEFTISTHEAP2_0_H

#include "IHeap.h"
#include "LeftHeap.h"

template<typename T>
struct VertexL : public Vertex<T> {
    int rank = 0;

    static int rk(VertexL *a) {
        if (a == nullptr) {
            return 0;
        } else return a->rank;
    }

    VertexL(T x) : Vertex<T>(x) {
        rank = 1;
    }

    void invariant_maintenance() {
        VertexL<T> *l = dynamic_cast<VertexL<T> *>(Vertex<T>::left);
        VertexL<T> *r = dynamic_cast<VertexL<T> *>(Vertex<T>::right);
        if (rk(l) < rk(r)) {
            std::swap(Vertex<T>::left, Vertex<T>::right);
            std::swap(l, r);
        }
        rank = rk(r) + 1;
    };
};

template<typename T>
class LeftistHeap2_0 : public LeftHeap<T> {
private:
public:
    void Insert(T x) {
        LeftistHeap2_0<T> *a = new LeftistHeap2_0(x);
        LeftHeap<T>::Merge(*a);
    }

    explicit LeftistHeap2_0<T>(T x) {
        VertexL<T> *r = new VertexL<T>(x);
        LeftHeap<T>::root = r;
    }

    LeftistHeap2_0<T>() : LeftHeap<T>() {}
};

#endif //HEAP_LEFTISTHEAP2_0_H
