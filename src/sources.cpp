#include "sources.h"

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

// template <typename T>
// const std::vector<T> SimuBlocks::SineWave(const unsigned NumOfSamples, const T Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay, const T Bias)
// {
//     // safety checks 
//     if (!NumOfSamples || !SamplesPerPeriod) 
//         throw std::invalid_argument("Number of samples and samples per period must be > 0");
    
//     // initialize vector
//     std::vector<T> vec (NumOfSamples, Bias); 

//     // fill in the vector
//     unsigned k = 0;
//     for (int i = PhaseDelay; i < NumOfSamples; ++i)
//     {
//         if (k == SamplesPerPeriod-1)
//             k = 0;
//         vec[i] += Amplitude * static_cast<T>(std::sin(2.f * static_cast<float>(M_PI) * static_cast<float>(k + PhaseDelay) / static_cast<float>(SamplesPerPeriod-1)));
//         k += 1;
//     }

//     return vec;
// }

// template const std::vector<int> SimuBlocks::SineWave(const unsigned NumOfSamples, const int Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay, const int Bias);
// template const std::vector<float> SimuBlocks::SineWave(const unsigned NumOfSamples, const float Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay, const float Bias);

template const std::vector<int> SimuBlocks::RandomNumber(const unsigned NumOfSamples, const int MinLimit, const int MaxLimit);
template const std::vector<float> SimuBlocks::RandomNumber(const unsigned NumOfSamples, const float MinLimit, const float MaxLimit);