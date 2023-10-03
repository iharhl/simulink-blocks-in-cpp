#ifndef _RAND_NUM_GEN_H
#define _RAND_NUM_GEN_H

#include "BasicBlock.h"
#include <random>

namespace SimuBlocks
{

template <typename T>
class RandomNumberGenerator : public BasicBlock<T>
{
public:
    RandomNumberGenerator(const T MinLimit, const T MaxLimit);
    ~RandomNumberGenerator();
    void Tick();
private:
    const T m_MinLimit;
    const T m_MaxLimit;
    using uniform_distribution_t = std::conditional<std::is_integral<T>::value,std::uniform_int_distribution<T>,std::uniform_real_distribution<T>>::type;
    std::mt19937 m_Generator; // pseudo-random generator
    uniform_distribution_t m_Distribution; // random number distribution
};

}

template<typename T>
SimuBlocks::RandomNumberGenerator<T>::RandomNumberGenerator(const T MinLimit,
                                                            const T MaxLimit)
                                                            :
                                                            m_MinLimit(MinLimit),
                                                            m_MaxLimit(MaxLimit),
                                                            m_Generator(std::random_device()()),
                                                            m_Distribution(MinLimit, MaxLimit)
{
    this->m_Output = 0;
};

template<typename T>
SimuBlocks::RandomNumberGenerator<T>::~RandomNumberGenerator() {};

template <typename T>
void SimuBlocks::RandomNumberGenerator<T>::Tick()
{
    this->m_Output = m_Distribution(m_Generator);
}

#endif