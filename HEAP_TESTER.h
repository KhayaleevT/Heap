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

const int SIZE = 1000, N = 1000000;

enum Key {
    BinomialHeapKey, SkewHeapKey, LeftistHeapKey
};

template<Key y>
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

    IHeap<int> *_create_Heap() {
        IHeap<int> *ans;
        if (y == BinomialHeapKey) {
            ans = new BinomialHeap<int>;
        }
        if (y == SkewHeapKey) {
            ans = new SkewHeap2_0<int>;
        }
        if (y == LeftistHeapKey) {
            ans = new LeftistHeap2_0<int>;
        }
        return ans;
    }

    void SetUp() override {
        heaps.resize(SIZE, nullptr);
        good_heaps.resize(SIZE, nullptr);
        for (int i = 0; i < SIZE; i++) {
            heaps[i] = _create_Heap();
        }
        _create_good_vector();
    }

    void TearDown() {
        for (size_t i = 0; i < heaps.size(); i++) {
            delete heaps[i];
            delete good_heaps[i];
        }
    }

    void tester(int key = 322, int amount = N, int ins_probability = 25,
                int get_min_probability = 25, int extract_min_probability = 25,
                int merge_probability = 25) {
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
                if (num == 139) {
                    std::cout << " ";
                }
                good_heaps[num]->Insert(value);
                heaps[num]->Insert(value);
            }
            if (x >= border_1 && x < border_2) {
                int num = rand() % heaps_left;
                if (!good_heaps[num]->Empty()) {
                    ASSERT_EQ(good_heaps[num]->GetMin(), heaps[num]->GetMin());
                }
            }
            if (x >= border_2 && x < border_3) {
                int num = rand() % heaps_left;
                if (!good_heaps[num]->Empty()) {
                    int val1 = good_heaps[num]->GetMin();
                    int val2 = heaps[num]->GetMin();
                    if (val1 != val2 || num == 139) {
                        std::cout << "-";
                    }
                    good_heaps[num]->ExtractMin();
                    heaps[num]->ExtractMin();
                    ASSERT_EQ(val1, val2);
                }
            }
            if (x >= border_3 && x < border_4) {
                int num1 = rand() % heaps_left;
                int num2 = rand() % heaps_left;
                if (num2 != num1) {
                    if (num1 == 139 || num2 == 139) {
                        std::cout << " ";
                    }
                    good_heaps[num1]->Merge(*good_heaps[num2]);
                    heaps[num1]->Merge(*heaps[num2]);
                    std::swap(good_heaps[num2], good_heaps.back());
                    std::swap(heaps[num2], heaps.back());
                    delete heaps.back();
                    delete good_heaps.back();
                    good_heaps.pop_back();
                    heaps.pop_back();
                    heaps_left--;
                }
            }
        }
    }

    void test1() {
        tester(322, N, 25, 25, 25, 25);
    }

    void test2() {
        tester(322, N, 50, 0, 25, 25);
    }

    void test3() {
        tester(322, N, 50, 0, 45, 5);
    }

    void test4() {
        tester(322, N, 70, 0, 20, 10);
    }

    void test5() {
        tester(322, N, 30, 0, 10, 60);
    }

};

typedef HeapTester<BinomialHeapKey> BinHeapTester;
typedef HeapTester<SkewHeapKey> SkewHeapTester;
typedef HeapTester<LeftistHeapKey> LeftistHeapTester;
TEST_F(BinHeapTester, BinomialHeap) {
    test1();
}

TEST_F(BinHeapTester, BinomialHeap_2) {
    test2();
}

TEST_F(BinHeapTester, BinomialHeap_3) {
    test3();
}

TEST_F(BinHeapTester, BinomialHeap_4) {
    test4();
}

TEST_F(BinHeapTester, BinomialHeap_5) {
    test5();
}

TEST_F(LeftistHeapTester, LeftistHeap) {
    test1();
}

TEST_F(LeftistHeapTester, LeftistHeap_2) {
    test2();
}

TEST_F(LeftistHeapTester, LeftistHeap_3) {
    test3();
}

TEST_F(LeftistHeapTester, LeftistHeap_4) {
    test4();
}

TEST_F(LeftistHeapTester, LeftistHeap_5) {
    test5();
}

TEST_F(SkewHeapTester, SkewHeap_1) {
    test1();
}

TEST_F(SkewHeapTester, SkewHeap_2) {
    test2();
}

TEST_F(SkewHeapTester, SkewHeap_3) {
    test3();
}

TEST_F(SkewHeapTester, SkewHeap_4) {
    test4();
}

TEST_F(SkewHeapTester, SkewHeap_5) {
    test5();
}


int test() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

#endif //HEAP_HEAP_TESTER_H
