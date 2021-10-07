#pragma once
#include <cassert>
#include "ArrayBase.h"

template<class T>
class OrderedArray : public ArrayBase<T> {
public:
    using ArrayBase<T>::ArrayBase;
    void push(T val) {
        assert(this->m_array != NULL);
        if (this->m_numElements == this->m_maxSize)
            this->Expand();

        int dest = 0;
        for (; dest < this->m_numElements && this->m_array[dest] < val; dest++);
        if (this->m_array[dest] == val) return;
        this->m_numElements++;
        int i = this->m_numElements - 1;
        for (; i > dest; i--)
            this->m_array[i] = this->m_array[i - 1];
        this->m_array[dest] = val;
    }

};