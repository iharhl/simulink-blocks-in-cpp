#ifndef _BASIC_BLOCK_H
#define _BASIC_BLOCK_H

namespace SimuBlocks
{

template <typename T>
class BasicBlock
{
public:
    virtual void Tick();
    T GetOutput() const;
    // virtual void SetInput();
protected:
    // T m_Input;
    T m_Output;
};

}

template<typename T>
void SimuBlocks::BasicBlock<T>::Tick() {}

template<typename T>
T SimuBlocks::BasicBlock<T>::GetOutput() const
{
    return m_Output;
}

#endif