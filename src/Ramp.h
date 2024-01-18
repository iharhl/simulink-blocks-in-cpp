#ifndef RAMP_H_
#define RAMP_H_

#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class Ramp : public BasicBlock<T>
{
public:
    Ramp(T Slope, unsigned StartRampSample, T InitialOutput);
    void Tick() override;
private:
    const T m_Slope;
    unsigned m_Counter;
    const unsigned m_StartRampSample;
};

}

template<typename T>
SimuBlocks::Ramp<T>::Ramp( const T Slope,
                           const unsigned StartRampSample,
                           const T InitialOutput)
                           :
                           m_Slope(Slope),
                           m_StartRampSample(StartRampSample)
{
    m_Counter = 0;
    this->m_Output = InitialOutput;
};

template <typename T>
void SimuBlocks::Ramp<T>::Tick()
{
    if (m_Counter < m_StartRampSample)
        m_Counter++;
    else
        this->m_Output += m_Slope;
}

#endif