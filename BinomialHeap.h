//
// Created by maent on 10.12.2019.
//

#ifndef UNTITLED_BINOMIALHEAP_H
#define UNTITLED_BINOMIALHEAP_H

#include "IHeap.h"

template<typename T>
class BinomialHeap : public IHeap<T> {
private:

    class VertexB {
    public:
        static VertexB *_Meld_Similar(VertexB *a, VertexB *b) {
            if (a->value > b->value) {
                std::swap(a, b);
            }
            VertexB *c = new VertexB(a, b, a->value);
            return c;
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

        VertexB *left;
        VertexB *right;
        T value;

        VertexB(T x) {
            left = nullptr;
            right = nullptr;
            value = x;
        }

        VertexB() {
            left = nullptr;
            right = nullptr;
        }

        VertexB(VertexB *l, VertexB *r, T val) {
            left = l;
            right = r;
            value = val;
        }
    };

    int min_index;
    vector<VertexB *> Tree;

    void _recount_min_index() {
        min_index = -1;
        for (size_t i = 0; i < Tree.size(); i++) {
            if (Tree[i] != nullptr) {
                min_index = i;
                break;
            }
        }
        for (size_t i = 1; (i < Tree.size()) && (min_index != -1); i++) {
            if (Tree[i] != nullptr && Tree[i]->value < Tree[min_index]->value) {
                min_index = i;
            }
        }
        if (Tree.empty())min_index = -1;
    }

public:
    ~BinomialHeap() {
        for (size_t i = 0; i < Tree.size(); i++) {
            if (Tree[i] != nullptr) {
                Tree[i]->_destruct();
            }
        }
    }

    BinomialHeap(BinomialHeap &) = delete;

    BinomialHeap &operator=(BinomialHeap &) = delete;

    explicit BinomialHeap<T>(T x) {
        VertexB *v = new VertexB(x);
        Tree.push_back(v);
        min_index = 0;
    }

    BinomialHeap() {
        min_index = -1;
    }

    BinomialHeap(vector<VertexB *> &x) {
        Tree = x;
        _recount_min_index();
    }

    void Merge(IHeap<T> &b1) {
        BinomialHeap<T> &b = dynamic_cast<BinomialHeap<T> &>(b1);
        VertexB *residue = new VertexB();
        bool Resid_Empty = true;
        size_t new_size = max(b.Tree.size(), Tree.size());
        Tree.resize(new_size, nullptr);
        b.Tree.resize(new_size, nullptr);
        for (int i = 0; i < Tree.size(); i++) {
            if (Tree[i] != nullptr && b.Tree[i] != nullptr) {
                VertexB *res = nullptr;
                if (!Resid_Empty) {
                    res = residue;
                }
                residue = VertexB::_Meld_Similar(Tree[i], (b.Tree[i]));
                Tree[i] = nullptr;
                if (!Resid_Empty) {
                    Tree[i] = res;
                }
                Resid_Empty = false;
                continue;
            }
            if (Tree[i] != nullptr) {
                if (!Resid_Empty) {
                    residue = VertexB::_Meld_Similar(residue, Tree[i]);
                    Tree[i] = nullptr;
                }
                continue;
            }
            if (b.Tree[i] != nullptr) {
                if (!Resid_Empty) {
                    residue = VertexB::_Meld_Similar(residue, b.Tree[i]);
                    b.Tree[i] = nullptr;
                } else {
                    Tree[i] = b.Tree[i];
                }
                continue;
            }
            if (!Resid_Empty) {
                Tree[i] = residue;
                Resid_Empty = true;
                continue;
            }
        }
        if (!Resid_Empty) {
            Tree.push_back(residue);
        }
        _recount_min_index();
        b.Tree.clear();
    }

    void Insert(T x) {
        BinomialHeap<T> c(x);
        Merge(c);
    }

    T GetMin() {
        return Tree[min_index]->value;
    }

    void ExtractMin() {
        VertexB *cur = Tree[min_index];
        Tree[min_index] = nullptr;
        if (min_index == Tree.size() - 1) {
            Tree.pop_back();
        }
        vector<VertexB *> resid;
        while (cur != nullptr && cur->right != nullptr) {
            resid.push_back(cur->right);
            VertexB *old_cur = cur;
            cur = cur->left;
            delete (old_cur);
        }
        if (cur != nullptr) {
            delete (cur);
        }
        reverse(resid.begin(), resid.end());
        BinomialHeap r(resid);
        Merge(r);
    }

    bool Empty() {
        return Tree.empty();
    }
};

#endif //UNTITLED_BINOMIALHEAP_H
