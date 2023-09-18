#ifndef _SINE_WAVE_H
#define _SINE_WAVE_H

#include "BasicBlock.h"
#include <numbers>

namespace SimuBlocks
{

template <typename T>
class SineWave : public BasicBlock<T>
{
public:
    SineWave(const T Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay, const T Bias);
    ~SineWave();
    void Tick();
private:
    unsigned m_Counter;
    const T m_Amplitude;
    const T m_Bias;
    const unsigned m_SamplesPerPeriod;
    const unsigned m_PhaseDelay;
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
    // this->m_Output = m_Amplitude * static_cast<T>(std::sin(2 * std::numbers::pi * m_PhaseDelay / (m_SamplesPerPeriod-1)));
    this->m_Output = 0;
};

template<typename T>
SimuBlocks::SineWave<T>::~SineWave() {}

template <typename T>
void SimuBlocks::SineWave<T>::Tick()
{
    if (m_Counter == m_SamplesPerPeriod-1)
        m_Counter = 0;

    this->m_Output = m_Amplitude * static_cast<T>(std::sin(2 * std::numbers::pi * (m_Counter + m_PhaseDelay) / (m_SamplesPerPeriod-1)));

    m_Counter++;
}

#endif