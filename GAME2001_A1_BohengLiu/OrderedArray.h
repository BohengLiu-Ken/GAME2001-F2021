#pragma once
#include <cassert>
#include "ArrayBase.h"

template<class T>
class OrderedArray : public ArrayBase<T> {
public:

    int push(T val) {
        assert(a_array != NULL);
        if (m_numElements == m_maxSize)
            Expand();

        int dest = 0;
        for (; dest < m_numElements && m_array[i] < val; dest++);
        if (m_array[dest] == val) return -1;
        int i = dest;
        for (; i < m_numElements; i++)
            m_array[i + 1] = m_array[i];
        m_array[dest] = val;
        return dest;
    }

};