#ifndef _TRANSFER_FUNCTION_H
#define _TRANSFER_FUNCTION_H

#include <vector>
#include <deque>
#include <iostream>
#include <utility>
#include "BasicBlock.h"

// for now...
#define TF_COEFF_NUM 3
#define TF_ORDER_MAX 2

namespace SimuBlocks
{

template <typename T>
class TransferFunction : public BasicBlock<T>
{
public:
    TransferFunction(const std::array<float,TF_COEFF_NUM>& NominatorCoefficients,
                     const std::array<float,TF_COEFF_NUM>& DenominatorCoefficients,
                     const float SamplingPeriod = 0.001);
    ~TransferFunction();
    void Tick();

private:
    void GetTFOrder();
    std::array<float,TF_COEFF_NUM> m_NominatorCoefficients; // inverse order - last is the lowest order
    std::array<float,TF_COEFF_NUM> m_DenominatorCoefficients;
    uint8_t m_TFOrder; // same as denominator order
    uint8_t m_NominatorOrder;
    std::array<std::pair<float,float>,TF_COEFF_NUM> m_TfInputTerms;
    std::array<std::pair<float,float>,TF_COEFF_NUM> m_TfOutputTerms;
    const float m_Dt;
    bool m_FirstStep;
};

}

template<typename T>
SimuBlocks::TransferFunction<T>::TransferFunction(const std::array<float,3>& NominatorCoefficients,
                                                  const std::array<float,3>& DenominatorCoefficients,
                                                  const float SamplingPeriod)
                                                  :
                                                  m_Dt(SamplingPeriod),
                                                  m_FirstStep(true)
{
    this->m_Output = 0;
    for (int i = 0; i < TF_COEFF_NUM; ++i)
    {
        // Initialize terms with zeros
        m_TfInputTerms[i] = std::make_pair(0, 0);
        m_TfOutputTerms[i] = std::make_pair(0, 0);
        // Swap the coefficients order
        m_NominatorCoefficients[i] = NominatorCoefficients[TF_ORDER_MAX-i];
        m_DenominatorCoefficients[i] = DenominatorCoefficients[TF_ORDER_MAX-i];
    }
    // Get order after coefficients swap
    GetTFOrder();
}


/* TODO: improve */
template<typename T>
void SimuBlocks::TransferFunction<T>::GetTFOrder()
{
    // Denominator
    for (uint8_t i = TF_ORDER_MAX; i >= 0; --i)
    {
        if (m_DenominatorCoefficients[i])
        {
            m_TFOrder = i;
            break;
        }
    }
    // Nominator
    for (uint8_t i = TF_ORDER_MAX; i >= 0; --i)
    {
        if (m_NominatorCoefficients[i])
        {
            if (i > m_TFOrder)
                std::exit(EXIT_FAILURE);
            else
                m_NominatorOrder = i;
                break;
        }
    }
}

template<typename T>
SimuBlocks::TransferFunction<T>::~TransferFunction() {}

template<typename T>
void SimuBlocks::TransferFunction<T>::Tick()
{
    // TODO: reverse the order
    // Solving input terms
    float SumOfInputTerms = 0;
    for (int i = 0; i <= m_NominatorOrder; ++i)
    {
        // Update
        m_TfInputTerms[i].first = m_TfInputTerms[i].second;
        // Calculate terms
        if (i == 0)
            m_TfInputTerms[i].second = this->m_Input;
        else
            m_TfInputTerms[i].second = (m_TfInputTerms[i-1].second - m_TfInputTerms[i-1].first) / m_Dt;

        SumOfInputTerms += m_TfInputTerms[i].second * m_NominatorCoefficients[i];
    } 

    // Solving output terms
    float SumOfOutputTerms = 0;
    for (int i = m_TFOrder-1; i >= 0; --i)
    {
        // Update
        m_TfOutputTerms[i].first = m_TfOutputTerms[i].second;
        // Calculate terms
        m_TfOutputTerms[i].second = m_TfOutputTerms[i].first + m_Dt * m_TfOutputTerms[i+1].second;

        SumOfOutputTerms += m_TfOutputTerms[i].second * m_DenominatorCoefficients[i];
    }

    m_TfOutputTerms[m_TFOrder].first = m_TfOutputTerms[m_TFOrder].second;
    m_TfOutputTerms[m_TFOrder].second = (SumOfInputTerms - SumOfOutputTerms) / m_DenominatorCoefficients[m_TFOrder];

    this->m_Output = m_TfOutputTerms[0].second;
}

#endif