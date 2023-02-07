#ifndef SOURCES_H_
#define SOURCES_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <random>

namespace SimuBlocks
{

// Constant
template <typename T>
const std::vector<T> Constant(const unsigned NumOfSamples, const T ConstValue);

// Random Number
template <typename T>
const std::vector<T> RandomNumber(const unsigned NumOfSamples, const T MinLimit = static_cast<T>(0), const T MaxLimit = static_cast<T>(1));

// Step
template <typename T>
const std::vector<T> Step(const unsigned NumOfSamples, const T InitValue, const T FinalValue, const unsigned StepSample);

// Pulse Generator
template <typename T>
const std::vector<T> PulseGenerator(const unsigned NumOfSamples, const T Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay = 0);

// Ramp
template <typename T>
const std::vector<T> Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const T InitialOutput);

template <typename T>
const std::vector<T> SineWave(const unsigned NumOfSamples, const T Amplitude, const unsigned SamplesPerPeriod, const unsigned PhaseDelay = 0, const T Bias = static_cast<T>(0));

}

#endif