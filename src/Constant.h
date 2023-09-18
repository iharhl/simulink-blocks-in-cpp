#ifndef _CONSTANT_H
#define _CONSTANT_H

#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class Constant : public BasicBlock<T>
{
public:
    Constant(const T ConstValue);
    ~Constant();
};

}

template<typename T>
SimuBlocks::Constant<T>::Constant(const T ConstValue)
{
    this->m_Output = ConstValue;
};

template<typename T>
SimuBlocks::Constant<T>::~Constant() {};

#endif