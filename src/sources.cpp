#include "sources.h"

template <typename T>
const std::vector<T> SimuBlocks::Step(const unsigned NumOfSamples, const T InitValue, const T FinalValue, const unsigned StepSample)
{

    std::vector<T> vec (NumOfSamples, InitValue);

    for (int i = StepSample; i < NumOfSamples; ++i)
    {
        vec[i] = FinalValue;
    }
    
    return vec;
}


const std::vector<int> SimuBlocks::PulseGenerator(const unsigned NumOfSamples, const int Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay)
{
    // safety checks 
    if (!NumOfSamples || !Period || !DutyCycle) 
        throw std::invalid_argument("Number of samples, period and duty cycle parameters must be > 0");

    // initialize vector
    std::vector<int> vec (NumOfSamples, 0);

    // calculate the pulse width
    const unsigned m_PulseWidth = (Period * DutyCycle) / 100;

    // signal period counter
    unsigned m_Counter = 0;

    // fill in the vector
    for (int i = PhaseDelay; i < NumOfSamples; ++i)
    {
        if (m_Counter < m_PulseWidth)
            vec[i] = Amplitude;
        else
            vec[i] = 0;
        m_Counter += 1;
        
        if (m_Counter == Period)
            m_Counter = 0;
    }

    return vec;
}