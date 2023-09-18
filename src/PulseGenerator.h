#ifndef _PULSE_GENERATOR_H
#define _PULSE_GENERATOR_H

#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class PulseGenerator : public BasicBlock<T>
{

public:
    PulseGenerator( const T Amplitude,
                    const unsigned Period,
                    const unsigned DutyCycle,
                    const unsigned PhaseDelay );
    ~PulseGenerator();
    void Tick();

private:
    unsigned m_Counter; // not a time or total tick time counter
    unsigned m_PhaseDelayCounter; // other way ?
    const T m_Amplitude;
    unsigned m_PhaseDelay;
    unsigned m_PulseWidth;
    const unsigned m_Period;
};

}

template <typename T>
SimuBlocks::PulseGenerator<T>::PulseGenerator( const T Amplitude,
                                               const unsigned Period,
                                               const unsigned DutyCycle, // [%]
                                               const unsigned PhaseDelay)
                                               :
                                               m_Amplitude(Amplitude),
                                               m_Period(Period),
                                               m_PhaseDelay(PhaseDelay)                                
{
    m_Counter = 0;
    m_PhaseDelayCounter = 0;
    m_PulseWidth = (Period * DutyCycle) / 100;
    this->m_Output = 0;
}

template <typename T>
SimuBlocks::PulseGenerator<T>::~PulseGenerator() {}

template <typename T>
void SimuBlocks::PulseGenerator<T>::Tick()
{
    if (m_PhaseDelayCounter < m_PhaseDelay)
    {
        m_PhaseDelayCounter++;
        return; // do nothing
    } else
    {
        m_PhaseDelay = 0; // meh

        if (m_Counter < m_PulseWidth)
            this->m_Output = m_Amplitude;
        else
            this->m_Output = 0;

        m_Counter++;
        if (m_Counter == m_Period)
            m_Counter = 0;
    }
        
}

#endif