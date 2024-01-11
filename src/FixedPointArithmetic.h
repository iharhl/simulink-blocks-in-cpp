#ifndef _FIXDT_H
#define _FIXDT_H

#include <cassert>
#include <bitset>

template <typename T, size_t FractionLength>
class fixdt
{
public:

    static_assert( FractionLength <= (sizeof(T)*8) );
    T FixedValue = T(0);
    
    fixdt() = default;
    
    fixdt(const double Value)
    {
        FixedValue = T(Value * double(1 << FractionLength) + (Value >= 0 ? 0.5 : -0.5));
    }
    
    fixdt(const float Value)
    {
        FixedValue = T(Value * float(1 << FractionLength) + (Value >= 0 ? 0.5f : -0.5f));
    }
    
private:
    static fixdt form(T v) { fixdt fi; fi.FixedValue = v; return fi; }
    
public:

    operator float() const
    {
        return float(FixedValue) / float(1 << FractionLength);
    }

    operator double() const
    {
        return double(FixedValue) / double(1 << FractionLength);
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
    
    // std::bitset<sizeof(T)*8> GetBinary(void)
    // {
    //     return std::bitset<sizeof(T)*8>(this->FixedValue);
    // }
};

#endif