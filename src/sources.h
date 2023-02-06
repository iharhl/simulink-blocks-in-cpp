#ifndef SOURCES_H_
#define SOURCES_H_

#include <iostream>
#include <array>
#include <vector>
#include <memory>

namespace SimuBlocks
{

// Constant
template <typename T>
const std::vector<T> Constant(const unsigned NumOfSamples, const T ConstValue);

// Step
template <typename T>
const std::vector<T> Step(const unsigned NumOfSamples, const T InitValue, const T FinalValue, const unsigned StepSample);

// Pulse Generator
template <typename T>
const std::vector<T> PulseGenerator(const unsigned NumOfSamples, const T Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay = 0);

// Ramp
template <typename T>
const std::vector<T> Ramp(const unsigned NumOfSamples, const float Slope, const unsigned StartRampSample, const T InitialOutput);
}

#endif