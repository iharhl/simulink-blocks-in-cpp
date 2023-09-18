#ifndef _RAMP_H
#define _RAMP_H

#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class Ramp : public BasicBlock<T>
{
public:
    Ramp(const T Slope, const unsigned StartRampSample, const T InitialOutput);
    ~Ramp();
    void Tick();
private:
    unsigned m_Counter;
    const unsigned m_StartRampSample;
    const T m_Slope;
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

template<typename T>
SimuBlocks::Ramp<T>::~Ramp() {};

template <typename T>
void SimuBlocks::Ramp<T>::Tick()
{
    m_Counter++;
    
    if (m_Counter < m_StartRampSample) {}
        /* Do nothing (output is the same) */
    else
        this->m_Output += m_Slope;
}

#endif