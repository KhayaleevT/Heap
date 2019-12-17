//
// Created by maent on 16.12.2019.
//

#ifndef HEAP_SKEWHEAP2_0_H
#define HEAP_SKEWHEAP2_0_H

#include "IHeap.h"
#include "LeftHeap.h"

template<typename T>
struct VertexS : public VertexLeft<T> {
    using VertexLeft<T>::VertexLeft;

    void invariant_maintenance() {
        std::swap(VertexLeft<T>::left, VertexLeft<T>::right);
    };
};

template<typename T>
class SkewHeap2_0 : public LeftHeap<T> {
private:
public:
    void Insert(T x) {
        SkewHeap2_0<T> *a = new SkewHeap2_0(x);
        LeftHeap<T>::Merge(*a);
    }

    explicit SkewHeap2_0<T>(T x) {
        VertexS<T> *r = new VertexS<T>(x);
        LeftHeap<T>::root = r;
    }

    SkewHeap2_0<T>() {
        LeftHeap<T>::root = nullptr;
    }
};

#endif //HEAP_SKEWHEAP2_0_H
