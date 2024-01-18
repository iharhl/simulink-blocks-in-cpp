#ifndef FIXDT_H_
#define FIXDT_H_

#include <cassert>
#include <bitset>

template <typename T, size_t FractionLength>
class fixdt
{
public:

    static_assert( FractionLength <= (sizeof(T)*8) );
    T FixedValue = T(0);
    
    fixdt() = default;
    
    explicit fixdt(const double Value)
    {
        FixedValue = T(Value * static_cast<double>(1 << FractionLength) + (Value >= 0 ? 0.5 : -0.5));
    }
    
    explicit fixdt(const float Value)
    {
        FixedValue = T(Value * static_cast<float>(1 << FractionLength) + (Value >= 0 ? 0.5f : -0.5f));
    }
    
private:
    static fixdt form(T v) { fixdt fi; fi.FixedValue = v; return fi; }
    
public:

    explicit operator float() const
    {
        return static_cast<float>(FixedValue) / static_cast<float>(1 << FractionLength);
    }

    explicit operator double() const
    {
        return static_cast<double>(FixedValue) / static_cast<double>(1 << FractionLength);
    }
    
    fixdt& operator = (const fixdt& f) = default;
    
    // Negate unary
    fixdt operator - ()
    {
        assert(std::is_signed<T>()); // check if the type is signed
        return form(-(this->FixedValue));
    }
    
    fixdt operator + (const fixdt& f)
    {
        return form(this->FixedValue + f.FixedValue);
    }
    
    fixdt& operator += (const fixdt& f)
    {
        this->FixedValue += f.FixedValue;
        return *this;
    }
    
    fixdt operator - (const fixdt& f)
    {
        return form(this->FixedValue - f.FixedValue);
    }
    
    fixdt& operator -= (const fixdt& f)
    {
        this->FixedValue -= f.FixedValue;
        return *this;
    }
    
    fixdt operator * (const fixdt& f)
    {
        return form(this->FixedValue * f.FixedValue >> FractionLength);
    }
    
    fixdt& operator *= (const fixdt& f)
    {
        this->FixedValue = this->FixedValue * f.FixedValue >> FractionLength;
        return *this;
    }
    
    fixdt operator / (const fixdt& f)
    {
        return form((this->FixedValue << FractionLength) * f.FixedValue);
    }
    
    fixdt& operator /= (const fixdt& f)
    {
        this->FixedValue = (this->FixedValue << FractionLength) / f.FixedValue;
        return *this;
    }

    bool operator == (const T val)
    {
        return T(this->FixedValue) == val;
    }
    
    std::bitset<sizeof(T)*8> GetBinary()
    {
        return std::bitset<sizeof(T)*8>(this->FixedValue);
    }
};

#endif