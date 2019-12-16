//
// Created by maent on 14.12.2019.
//

#ifndef HEAP_TESTHEAP_H
#define HEAP_TESTHEAP_H

#include "IHeap.h"

template<typename T>
class TestHeap : public IHeap<T> {
    std::multiset<T> s;
public:
    void Merge(IHeap<T> &b) {
        TestHeap<T> &a = dynamic_cast<TestHeap<T> &>(b);
        s.insert(a.s.begin(), a.s.end());
    }

    T GetMin() {
        return *s.begin();
    }

    void ExtractMin() {
        if (!s.empty()) {
            s.erase(s.begin());
        }
    }

    void Insert(T x) {
        s.insert(x);
    }

    bool Empty() {
        return s.empty();
    }

    int size() {
        return s.size();
    }
};

#endif //HEAP_TESTHEAP_H
