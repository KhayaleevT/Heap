//
// Created by maent on 14.12.2019.
//

#ifndef HEAP_HEAP_TESTER_H
#define HEAP_HEAP_TESTER_H

#include "IHeap.h"
#include "BinomialHeap.h"
#include "SkewHeap2_0.h"
#include "LeftistHeap2_0.h"
#include <random>
#include <gtest/gtest.h>

const int SIZE = 1000, N = 100000;

void tester(vector<IHeap<int> *> tested, vector<IHeap<int> *> in_test, int key, int amount, int ins_probability,
            int get_min_probability, int extract_min_probability,
            int merge_probability) {
    srand(key);
    int heaps_left = SIZE;
    for (int i = 0; i < amount; i++) {
        if (heaps_left == 0)break;
        int x = rand() % 100;
        int border_1 = ins_probability;
        int border_2 = border_1 + get_min_probability;
        int border_3 = border_2 + extract_min_probability;
        int border_4 = border_3 + merge_probability;
        if (x >= 0 && x < border_1) {
            int value = rand();
            int num = rand() % heaps_left;
            tested[num]->Insert(value);
            in_test[num]->Insert(value);
        }
        if (x >= border_1 && x < border_2) {
            int num = rand() % heaps_left;
            if (!tested[num]->Empty()) {
                ASSERT_EQ(tested[num]->GetMin(), in_test[num]->GetMin());
            }
        }
        if (x >= border_2 && x < border_3) {
            int num = rand() % heaps_left;
            if (!tested[num]->Empty()) {
                ASSERT_EQ(tested[num]->GetMin(), in_test[num]->GetMin());
                tested[num]->ExtractMin();
                in_test[num]->ExtractMin();
            }
        }
        if (x >= border_3 && x < border_4) {
            int num1 = rand() % heaps_left;
            int num2 = rand() % heaps_left;
            if (num2 != num1) {
                tested[num1]->Merge(*tested[num2]);
                in_test[num1]->Merge(*in_test[num2]);
                std::swap(tested[num2], tested.back());
                std::swap(in_test[num2], in_test.back());
                tested.pop_back();
                in_test.pop_back();
                heaps_left--;
            }
        }
    }
}

enum {
    BinomialHeapKey, SkewHeapKey, LeftistHeapKey
};

class HeapTester : public ::testing::Test {
protected:
    vector<IHeap<int> *> heaps;
    vector<IHeap<int> *> good_heaps;

    void _create_good_vector() {
        good_heaps.resize(SIZE, nullptr);
        for (int i = 0; i < SIZE; i++) {
            good_heaps[i] = new TestHeap<int>;
        }
    }

    IHeap<int> *_create_Heap(int x) {
        IHeap<int> *ans;
        if (x == BinomialHeapKey) {
            ans = new BinomialHeap<int>;
        }
        if (x == SkewHeapKey) {
            ans = new SkewHeap2_0<int>;
        }
        if (x == LeftistHeapKey) {
            ans = new LeftistHeap2_0<int>;
        }
        return ans;
    }

    void SetUp(int x) {
        heaps.resize(SIZE, nullptr);
        good_heaps.resize(SIZE, nullptr);
        for (int i = 0; i < SIZE; i++) {
            heaps[i] = _create_Heap(x);
        }
        _create_good_vector();
    }

    void TearDown() {
        for (int i = 0; i < SIZE; i++) {
            delete heaps[i];
            delete good_heaps[i];
        }
    }

};

TEST_F(HeapTester, BinomialHeap) {
    SetUp(BinomialHeapKey);
    tester(good_heaps, heaps, 322, N, 25, 25, 25, 25);
}

TEST_F(HeapTester, BinomialHeap_2) {
    SetUp(BinomialHeapKey);
    tester(good_heaps, heaps, 322, N, 50, 0, 25, 25);
}

TEST_F(HeapTester, LeftistHeap) {
    SetUp(LeftistHeapKey);
    tester(good_heaps, heaps, 322, N, 25, 25, 25, 25);
}

TEST_F(HeapTester, LeftistHeap_2) {
    SetUp(LeftistHeapKey);
    tester(good_heaps, heaps, 322, N, 50, 0, 45, 5);
}

TEST_F(HeapTester, LeftistHeap_3) {
    SetUp(LeftistHeapKey);
    tester(good_heaps, heaps, 322, N, 25, 0, 25, 50);
}

TEST_F(HeapTester, SkewHeap) {
    SetUp(SkewHeapKey);
    tester(good_heaps, heaps, 322, N, 25, 25, 25, 25);
}


int test() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

#endif //HEAP_HEAP_TESTER_H
