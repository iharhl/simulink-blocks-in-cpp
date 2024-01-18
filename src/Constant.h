#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class Constant : public BasicBlock<T>
{
public:
    explicit Constant(T ConstValue);
};

}

template<typename T>
SimuBlocks::Constant<T>::Constant(const T ConstValue)
{
    this->m_BlockType = OutputOnly;
    this->m_Output = ConstValue;
};

#endif