#ifndef _STEP_H
#define _STEP_H

#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class Step : public BasicBlock<T>
{
public:
    Step(const T InitValue, const T FinalValue, const unsigned StepSample);
    ~Step();
    void Tick();
private:
    unsigned m_Counter;
    const unsigned m_StepSample;
    const T m_InitValue;
    const T m_FinalValue;
};

}

template<typename T>
SimuBlocks::Step<T>::Step( const T InitValue,
                           const T FinalValue,
                           const unsigned StepSample)
                           :
                           m_InitValue(InitValue),
                           m_FinalValue(FinalValue),
                           m_StepSample(StepSample)
{
    m_Counter = 0;
    this->m_Output = InitValue;
};

template<typename T>
SimuBlocks::Step<T>::~Step() {}

template<typename T>
void SimuBlocks::Step<T>::Tick()
{
    if (m_Counter+1 < m_StepSample)
    {
        m_Counter++;
        this->m_Output = m_InitValue;
    } else
    {
        this->m_Output = m_FinalValue;
    }
}

#endif