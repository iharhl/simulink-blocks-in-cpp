#ifndef _TRANSFER_FUNCTION_H
#define _TRANSFER_FUNCTION_H

#include <utility>
#include "BasicBlock.h"

// TODO: improve the defines
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

    /* Array that holds coefficients; order is reversed */
    std::array<float,TF_COEFF_NUM> m_NominatorCoefficients;
    std::array<float,TF_COEFF_NUM> m_DenominatorCoefficients;

    /* Order of denominator (= order of TF) and nominator */
    uint8_t m_TFOrder;
    uint8_t m_NominatorOrder;

    /* Input terms (u, ud, udd...) and Output terms (y, yd, ydd...) arrays.
       Contain a pair of values (prev and current ones). */
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

template<typename T>
void SimuBlocks::TransferFunction<T>::GetTFOrder()
{
    // Get order of denominator (= of TF)
    for (uint8_t i = TF_ORDER_MAX; i >= 0; --i)
    {
        if (m_DenominatorCoefficients[i])
        {
            m_TFOrder = i;
            break;
        }
    }
    // Get order of nominator
    for (uint8_t i = TF_ORDER_MAX; i >= 0; --i)
    {
        if (m_NominatorCoefficients[i])
        {
            if (i > m_TFOrder)
                // Order of nom cannot be higher than denom
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
    // Solving input terms
    float SumOfInputTerms = 0;
    for (int i = 0; i <= m_NominatorOrder; ++i)
    {
        // Update the prev value with the last current
        m_TfInputTerms[i].first = m_TfInputTerms[i].second;

        // Calculation
        if (i == 0)
            // Index 0 means input term (u)
            m_TfInputTerms[i].second = this->m_Input;
        else
            // Others calculated through finding derivative of lower order term (e.g. ud = derivative(u))
            m_TfInputTerms[i].second = (m_TfInputTerms[i-1].second - m_TfInputTerms[i-1].first) / m_Dt;

        // Sum up the input term * its coefficient
        SumOfInputTerms += m_TfInputTerms[i].second * m_NominatorCoefficients[i];
    } 

    // Solving output terms
    float SumOfOutputTerms = 0;
    for (int i = m_TFOrder-1; i >= 0; --i) // start from highest order term - 1
    {
        // Update the prev value with the last current
        m_TfOutputTerms[i].first = m_TfOutputTerms[i].second;
        
        // Calculate intergral
        m_TfOutputTerms[i].second = m_TfOutputTerms[i].first + m_Dt * m_TfOutputTerms[i+1].second;

        // Sum up the output term * its coefficient
        SumOfOutputTerms += m_TfOutputTerms[i].second * m_DenominatorCoefficients[i];
    }

    // Update prev value and calculate the highest order output term
    m_TfOutputTerms[m_TFOrder].first = m_TfOutputTerms[m_TFOrder].second;
    m_TfOutputTerms[m_TFOrder].second = (SumOfInputTerms - SumOfOutputTerms) / m_DenominatorCoefficients[m_TFOrder];

    // Assign the lowest order output term (y) to the output if the TF
    this->m_Output = m_TfOutputTerms[0].second;
}

#endif