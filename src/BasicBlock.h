#ifndef BASIC_BLOCK_H_
#define BASIC_BLOCK_H_

namespace SimuBlocks
{

enum BlockIOType { Unknown, InputOnly, OutputOnly, InputOutput };

template <typename T>
class BasicBlock
{
public:
    virtual ~BasicBlock() = default;
    virtual void Tick();
    T GetOutput() const;
    virtual void SetInput(T InputValue);
protected:
    T m_Input;
    T m_Output;
    BlockIOType m_BlockType = Unknown;
};

}

template<typename T>
void SimuBlocks::BasicBlock<T>::Tick() {}

template<typename T>
void SimuBlocks::BasicBlock<T>::SetInput(T InputValue)
{
    assert(this->m_BlockType != OutputOnly);
    m_Input = InputValue;
}

template<typename T>
T SimuBlocks::BasicBlock<T>::GetOutput() const
{
    return m_Output;
}

#endif