#include "sources.h"


template <typename T>
const std::vector<T> SimuBlocks::Constant(const unsigned NumOfSamples, const T ConstValue)
{
    // safety checks
    if (!NumOfSamples)
        throw std::invalid_argument("Number of samples must be > 0");

    // fill in the vector    
    std::vector<T> vec (NumOfSamples, ConstValue);

    return vec;
} 

template <typename T>
const std::vector<T> SimuBlocks::RandomNumber(const unsigned NumOfSamples, const T MinLimit, const T MaxLimit)
{
    // safety checks
    if (!NumOfSamples)
        throw std::invalid_argument("Number of samples must be > 0");
    
    // random uniform generator
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(static_cast<double>(MinLimit), static_cast<double>(MaxLimit));

    // initialize vector
    std::vector<T> vec (NumOfSamples);

    // fill in the vector
    for (int i = 0; i < NumOfSamples; ++i)
    {
        vec[i] = static_cast<T>(distrib(gen));
    }

    return vec;
} 

template <typename T>
const std::vector<T> SimuBlocks::Step(const unsigned NumOfSamples, const T InitValue, const T FinalValue, const unsigned StepSample)
{
    // safety checks
    if (!NumOfSamples)
        throw std::invalid_argument("Number of samples must be > 0");
    if (StepSample > NumOfSamples)
        throw std::invalid_argument("Sample at which step is happening is > number of samples");
    
    // initialize vector
    std::vector<T> vec (NumOfSamples, InitValue);

    // fill in the vector
    for (int i = StepSample-1; i < NumOfSamples; ++i)
    {
        vec[i] = FinalValue;
    }
    
    return vec;
}

template <typename T>
const std::vector<T> SimuBlocks::PulseGenerator(const unsigned NumOfSamples, const T Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay)
{
    // safety checks 
    if (!NumOfSamples || !Period || !DutyCycle) 
        throw std::invalid_argument("Number of samples, period and duty cycle parameters must be > 0");
    if (PhaseDelay > NumOfSamples)
        throw std::invalid_argument("Phase delay is > number of samples");

    // initialize vector
    std::vector<T> vec (NumOfSamples, 0);

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

template <typename T>
const std::vector<T> SimuBlocks::Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const T InitialOutput)
{
    // safety checks 
    if (!NumOfSamples || !StartRampSample) 
        throw std::invalid_argument("Number of samples and start ramp must be > 0");
    if (StartRampSample > NumOfSamples)
        throw std::invalid_argument("The sample at which slope begins is > number of samples");

    // initialize vector
    std::vector<T> vec (NumOfSamples, InitialOutput);

    // slope -> difference between consecutive samples
    T m_Diff = static_cast<T>(Slope);

    // fill in the vector
    for (int i = StartRampSample-1; i < NumOfSamples; ++i)
    {
        if (!i)
            vec[i] = InitialOutput;
        else
            vec[i] = vec[i-1] + m_Diff;
    }

    return vec;

}

template <typename T>
const std::vector<T> SimuBlocks::SineWave(const unsigned NumOfSamples, const T Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay, const T Bias)
{
    // TODO: safety checks
    
    // initialize vector
    std::vector<T> vec (NumOfSamples, Bias); 

    // fill in the vector
    unsigned k = 0;
    for (int i = PhaseDelay; i < NumOfSamples; ++i)
    {
        if (k == SamplesPerPeriod-1)
            k = 0;
        vec[i] += Amplitude * static_cast<T>(std::sin(2.f * static_cast<float>(M_PI) * static_cast<float>(k + PhaseDelay) / static_cast<float>(SamplesPerPeriod-1)));
        k += 1;
    }

    return vec;
}



// Explicit instantiation of template

template const std::vector<int> SimuBlocks::Step(const unsigned NumOfSamples, const int InitValue, const int FinalValue, const unsigned StepSample);
template const std::vector<float> SimuBlocks::Step(const unsigned NumOfSamples, const float InitValue, const float FinalValue, const unsigned StepSample);
template const std::vector<size_t> SimuBlocks::Step(const unsigned NumOfSamples, const size_t InitValue, const size_t FinalValue, const unsigned StepSample);
template const std::vector<std::uint8_t> SimuBlocks::Step(const unsigned NumOfSamples, const std::uint8_t InitValue, const std::uint8_t FinalValue, const unsigned StepSample);
template const std::vector<std::uint16_t> SimuBlocks::Step(const unsigned NumOfSamples, const std::uint16_t InitValue, const std::uint16_t FinalValue, const unsigned StepSample);

template const std::vector<int> SimuBlocks::PulseGenerator(const unsigned NumOfSamples, const int Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay);
template const std::vector<float> SimuBlocks::PulseGenerator(const unsigned NumOfSamples, const float Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay);
template const std::vector<size_t> SimuBlocks::PulseGenerator(const unsigned NumOfSamples, const size_t Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay);
template const std::vector<std::uint8_t> SimuBlocks::PulseGenerator(const unsigned NumOfSamples, const std::uint8_t Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay);
template const std::vector<std::uint16_t> SimuBlocks::PulseGenerator(const unsigned NumOfSamples, const std::uint16_t Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay);

template const std::vector<int> SimuBlocks::Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const int InitialOutput);
template const std::vector<float> SimuBlocks::Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const float InitialOutput);
template const std::vector<size_t> SimuBlocks::Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const size_t InitialOutput);
template const std::vector<std::uint8_t> SimuBlocks::Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const std::uint8_t InitialOutput);
template const std::vector<std::uint16_t> SimuBlocks::Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const std::uint16_t InitialOutput);

template const std::vector<int> SimuBlocks::Constant(const unsigned NumOfSamples, const int ConstValue);
template const std::vector<float> SimuBlocks::Constant(const unsigned NumOfSamples, const float ConstValue);
template const std::vector<size_t> SimuBlocks::Constant(const unsigned NumOfSamples, const size_t ConstValue);
template const std::vector<std::uint8_t> SimuBlocks::Constant(const unsigned NumOfSamples, const std::uint8_t ConstValue);
template const std::vector<std::uint16_t> SimuBlocks::Constant(const unsigned NumOfSamples, const std::uint16_t ConstValue);

template const std::vector<int> SimuBlocks::SineWave(const unsigned NumOfSamples, const int Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay, const int Bias);
template const std::vector<float> SimuBlocks::SineWave(const unsigned NumOfSamples, const float Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay, const float Bias);

template const std::vector<int> SimuBlocks::RandomNumber(const unsigned NumOfSamples, const int MinLimit, const int MaxLimit);
template const std::vector<float> SimuBlocks::RandomNumber(const unsigned NumOfSamples, const float MinLimit, const float MaxLimit);