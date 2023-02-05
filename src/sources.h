#ifndef SOURCES_H_
#define SOURCES_H_

#include <iostream>
#include <array>
#include <vector>
#include <memory>

namespace SimuBlocks
{
// Step
template <typename T>
const std::vector<T> Step(const unsigned NumOfSamples, const T InitValue, const T FinalValue, const unsigned StepSample);

// Pulse Generator
const std::vector<int> PulseGenerator(const unsigned NumOfSamples, const int Amplitude, const unsigned Period, const unsigned DutyCycle, const unsigned PhaseDelay = 0);
}

#endif