//
// Created by maent on 14.12.2019.
//

#ifndef UNTITLED_IHEAP_H
#define UNTITLED_IHEAP_H

#include <iostream>
#include<vector>
#include<algorithm>
#include<set>

using std::vector;
using std::pair;
using std::max;

template<typename T>
class IHeap {
public:
    virtual void Merge(IHeap<T> &) = 0;

    virtual T GetMin() = 0;

    virtual void ExtractMin() = 0;

    virtual void Insert(T x) = 0;

    virtual bool Empty() = 0;

    virtual ~IHeap() = default;
};

#endif //UNTITLED_IHEAP_H
