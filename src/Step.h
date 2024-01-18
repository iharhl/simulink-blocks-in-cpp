#ifndef STEP_H_
#define STEP_H_

#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class Step : public BasicBlock<T>
{
public:
    Step(T InitValue, T FinalValue, unsigned StepSample);
    void Tick() override;
private:
    const T m_InitValue;
    const T m_FinalValue;
    const unsigned m_StepSample;
    unsigned m_Counter;
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