#ifndef SINE_WAVE_H_
#define SINE_WAVE_H_

#include "BasicBlock.h"
#include <numbers>
#include <cmath>

namespace SimuBlocks
{

template <typename T>
class SineWave : public BasicBlock<T>
{
public:
    SineWave(T Amplitude, unsigned SamplesPerPeriod, unsigned PhaseDelay, T Bias);
    void Tick() override;
private:
    const T m_Amplitude;
    const unsigned m_SamplesPerPeriod;
    const unsigned m_PhaseDelay; // discrete phase shift
    const T m_Bias;
    unsigned m_Counter;
};

}

template<typename T>
SimuBlocks::SineWave<T>::SineWave( const T Amplitude,
                                   const unsigned SamplesPerPeriod,
                                   const unsigned PhaseDelay,
                                   const T Bias)
                                   :
                                   m_Amplitude(Amplitude),
                                   m_SamplesPerPeriod(SamplesPerPeriod),
                                   m_PhaseDelay(PhaseDelay),
                                   m_Bias(Bias)
{
    m_Counter = 0;
    this->m_Output = 0;
};

template <typename T>
void SimuBlocks::SineWave<T>::Tick()
{
    if (m_Counter == m_SamplesPerPeriod-1)
        m_Counter = 0;

    this->m_Output = m_Amplitude * static_cast<T>(std::sin(2 * std::numbers::pi * (m_Counter + m_PhaseDelay) /
        (m_SamplesPerPeriod-1)));

    m_Counter++;
}

#endif