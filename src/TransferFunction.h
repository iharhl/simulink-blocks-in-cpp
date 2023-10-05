#ifndef _TRANSFER_FUNCTION_H
#define _TRANSFER_FUNCTION_H

#include <vector>
#include <deque>
#include <iostream>
#include <utility>
#include "BasicBlock.h"

namespace SimuBlocks
{

template <typename T>
class TransferFunction : public BasicBlock<T>
{
public:
    TransferFunction(const std::array<float,3>& NominatorCoefficients,
                     const std::array<float,3>& DenominatorCoefficients,
                     const float SamplingPeriod = 0.001);
    ~TransferFunction();
    void Tick();

private:
    uint8_t GetNominatorOrder() const;
    uint8_t GetDenominatorOrder() const;
    const float m_Dt;
    std::array<float,3> m_Nominator;
    std::array<float,3> m_Denominator;

    struct
    {
        float ud0;
        float udd0;
        float y0;
        float yd0;
    } m_TfTermsInitCond;

    struct
    {
        std::pair<float,float> u;
        std::pair<float,float> ud;
        std::pair<float,float> udd;
        std::pair<float,float> y;
        std::pair<float,float> yd;
        std::pair<float,float> ydd;
    } m_TfTerms;

    bool m_FirstStep;
};

}

template<typename T>
SimuBlocks::TransferFunction<T>::TransferFunction(const std::array<float,3>& NominatorCoefficients,
                                                  const std::array<float,3>& DenominatorCoefficients,
                                                  const float SamplingPeriod)
                                                  :
                                                  m_Dt(SamplingPeriod),
                                                  m_Nominator(NominatorCoefficients),
                                                  m_Denominator(DenominatorCoefficients),
                                                  m_FirstStep(true)
{
    this->m_Output = 0;

    m_TfTermsInitCond.y0 = 0.0;
    m_TfTermsInitCond.ud0 = 0.0;
    m_TfTermsInitCond.udd0 = 0.0;
    m_TfTermsInitCond.yd0 = 0.0;

    m_TfTerms.u = std::make_pair(this->m_Input, 0.f);
    m_TfTerms.ud = std::make_pair(0.f, 0.f);
    m_TfTerms.udd = std::make_pair(0.f, 0.f);
    m_TfTerms.y = std::make_pair(0.f, 0.f);
    m_TfTerms.yd = std::make_pair(0.f, 0.f);
    m_TfTerms.ydd = std::make_pair(0.f, 0.f);
}

template<typename T>
uint8_t SimuBlocks::TransferFunction<T>::GetNominatorOrder() const
{
    uint8_t count = 0;
    for (auto &i : m_Nominator)
    {
        if (!i) { ++count; }
    }
    return count;
}

template<typename T>
uint8_t SimuBlocks::TransferFunction<T>::GetDenominatorOrder() const
{
    uint8_t count = 0;
    for (auto &i : m_Denominator)
    {
        if (!i) { ++count; }
    }
    return count;
}

template<typename T>
SimuBlocks::TransferFunction<T>::~TransferFunction() {}

template<typename T>
void SimuBlocks::TransferFunction<T>::Tick()
{
    m_TfTerms.u.first = m_TfTerms.u.second;
    m_TfTerms.u.second = this->m_Input;

    if (m_FirstStep)
    {
        m_TfTerms.ud.second = m_TfTermsInitCond.ud0;
        m_TfTerms.yd.second = m_TfTermsInitCond.yd0;
        m_TfTerms.y.second = m_TfTermsInitCond.y0;
        m_FirstStep = false;
    }
    else
    {
        m_TfTerms.ud.second = (m_TfTerms.u.second - m_TfTerms.u.first) / m_Dt;
        m_TfTerms.udd.second = (m_TfTerms.ud.second - m_TfTerms.ud.first) / m_Dt;
        m_TfTerms.yd.second = m_TfTerms.yd.first + m_Dt * m_TfTerms.ydd.first;
        m_TfTerms.y.second = m_TfTerms.y.first + m_Dt * m_TfTerms.yd.first;
    }
    m_TfTerms.ydd.second = (m_Nominator[2]*m_TfTerms.udd.second + m_Nominator[1]*m_TfTerms.ud.second + m_Nominator[0]*m_TfTerms.u.second - m_Denominator[1]*m_TfTerms.yd.second - m_Denominator[0]*m_TfTerms.y.second) / m_Denominator[2];
    this->m_Output = m_TfTerms.ydd.second;

    // Update
    m_TfTerms.ud.first = m_TfTerms.ud.second;
    m_TfTerms.udd.first = m_TfTerms.udd.second;
    m_TfTerms.y.first = m_TfTerms.y.second;
    m_TfTerms.yd.first = m_TfTerms.yd.second;
    m_TfTerms.ydd.first = m_TfTerms.y.second;
}

#endif