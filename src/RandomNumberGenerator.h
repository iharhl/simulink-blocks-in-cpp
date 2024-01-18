#ifndef RAND_NUM_GEN_H_
#define RAND_NUM_GEN_H_

#include "BasicBlock.h"
#include <random>

namespace SimuBlocks
{

template <typename T>
class RandomNumberGenerator : public BasicBlock<T>
{
public:
    RandomNumberGenerator(T MinLimit, T MaxLimit);
    void Tick() override;
private:
    const T m_MinLimit;
    const T m_MaxLimit;
    using uniform_distribution_t = std::conditional_t<std::is_integral_v<T>,std::uniform_int_distribution<T>,
                                    std::uniform_real_distribution<T>>;
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

template <typename T>
void SimuBlocks::RandomNumberGenerator<T>::Tick()
{
    this->m_Output = m_Distribution(m_Generator);
}

#endif