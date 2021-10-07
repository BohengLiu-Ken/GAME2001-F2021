#pragma once

#include <cassert>
#include "ArrayBase.h"

template<class T>
class UnorderedArray : public ArrayBase<T> {
    using ArrayBase<T>::ArrayBase;
};