#ifndef _FLOAT_HH_
#define _FLOAT_HH_

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <cmath>
#include <bitset>
#include <sstream>
#include <stdexcept>

#include "common.h"


template<int EXP, int FRAC> class FloatBase;
typedef FloatBase<4, 3> float8;

template<int EXP, int FRAC>
class FloatBase
{
    private:
        static constexpr int BIAS = (1 << (EXP - 1)) - 1;
        static constexpr u64 EXPMASK = (1 << EXP) - 1;
    private:
        struct _Data{
            u64 frac : FRAC;
            u64 exp : EXP;
            int sign : 1;
        }__attribute__((packed)) data;

    public:
        /* Constructor from binary value */
        FloatBase(void * val) { memcpy(&data, val, sizeof(data));  }

        /* visit data */
        std::string to_precise() const;
        Fraction to_fraction() const;
        double to_double() const;
        std::string to_binary() const;
        std::string to_string() const;

        bool isNaN() const {return data.exp == EXPMASK && data.frac;}
        bool isInf() const {return data.exp == EXPMASK &&!data.frac;}

    public:
        static FloatBase Build(i64 data);
        static FloatBase Build(const Fraction & f);
        static constexpr int LENGTH = 1 + EXP + FRAC;
        static constexpr int EXP_LEN = EXP;
        static constexpr int FRAC_LEN = FRAC;

    public:
};


/* ====== HELPER FUNCTIONS ====== */

/** 
 * Function: doRound(data)
 * round the data to given FRAC bits
 * @param: exp -- the pointer points to the exp value
 *                it will be add 1 if frac overflows
 * @returns: aligned frac data
 */
template<int FRAC> u64 doRound(u64 data, u64 *exp = nullptr, bool denorm = false)
{
    int len;
    u64 frac;
    len = 64 - __builtin_clzll(data);
    auto _round = [](u64 data, int len, int remain)
    {
        u64 frac;
        int shift = len - remain;//FRAC - 1;
        int srg;
        if(shift == 1)
        {
            srg = (data & 3) << 1;
            frac = data >> 1;
        }
        else
        {
            frac = data >> (shift - 2);
            srg = frac & 7;
            frac >>= 2;
        }

        switch(srg)
        {
            case 3:
            case 7:
            case 6:                
                ++frac;break;
            default:
                break;
        }
        return frac;
    };

    if(denorm)
    {
        if(len <= FRAC) frac = data;
        else
            frac = _round(data, len, FRAC);
        if(exp && (64 - __builtin_clzll(frac)) > FRAC)
            *exp += 1;
        return frac & ((1 << FRAC) - 1);
    }

    if(len-1 <= FRAC) //no round
    {
        frac = data ^ (1 << (len - 1));
        frac <<= (FRAC - len + 1);
    } 
    else    //do round
        frac = _round(data, len, FRAC + 1);
    if(exp && (64 - __builtin_clzll(frac)) > FRAC + 1)
        *exp += 1;
    return frac & ((1 << FRAC) - 1) ;
}




/* ====== TEMPLATE IMPLEMENTATIONS ====== */

template<int EXP, int FRAC>
std::string FloatBase<EXP,FRAC>::to_precise() const
{
    /* sign bit */
    std::string ret;
    if(data.sign) ret += "-";

    /* 0 inf NaN */
    if(!data.exp && !data.frac)
        return ret + "0";
    if(isNaN()) return "NaN";
    if(isInf()) return ret + "inf";

    /* calculate E */
    i64 E = (data.exp - BIAS);

    /* calculate precise number */
    u64 upper = data.frac + (data.exp ? (1 << FRAC) : 0);
    u64 lower = 1 << FRAC;
    if(E > 0) upper *= (1<<E);
    else if (E < 0) lower *= (1<<(data.exp ? -E : -E-1));

    /* get final data */
    Fraction f{data.sign, upper, lower};
    return f.to_string();
}

template<int EXP, int FRAC>
Fraction FloatBase<EXP, FRAC>::to_fraction() const
{
    i64 E = (data.exp - BIAS);
    u64 upper = data.frac + (data.exp ? (1 << FRAC) : 0);
    u64 lower = 1 << FRAC;
    if(E > 0) upper *= (1<<E);
    else if (E < 0) lower *= (1<<(data.exp ? -E : -E-1));
    return Fraction(data.sign, upper, lower);
}

template<int EXP, int FRAC>
double FloatBase<EXP, FRAC>::to_double() const
{
    if(isNaN()) return NAN;
    if(isInf()) return data.sign ? -INFINITY : INFINITY;
    i64 E = (data.exp - BIAS);
    /* calculate precise number */
    u64 upper = data.frac + (data.exp ? (1 << FRAC) : 0);
    u64 lower = 1 << FRAC;
    if(E > 0) upper *= (1<<E);
    else if (E < 0) lower *= (1<<(data.exp ? -E : -E-1));

    double ret = 0;
    if(upper && lower)
        ret = static_cast<double>(upper) / static_cast<double>(lower);
    if(data.sign) ret *= -1;
    return ret;
}

template<int EXP, int FRAC>
std::string FloatBase<EXP, FRAC>::to_binary() const
{
    u64 val;
    memcpy(&val, &data, sizeof(this->data));
    std::bitset<1+EXP+FRAC> set(val); 
    std::string ret;
    std::stringstream sout;
    return set.to_string();
}

template<int EXP, int FRAC>
std::string FloatBase<EXP, FRAC>::to_string() const
{
    std::stringstream str;
    return "Binary Value : " + to_binary() +
        ", Double Value : " + std::to_string(to_double()) +
        ", Precise Value : " + to_precise();
}

template<int EXP, int FRAC>
std::ostream & operator<<(std::ostream & o, const FloatBase<EXP, FRAC> & f)
{
    o<<f.to_string();
    return o;
}

template<int EXP, int FRAC>
FloatBase<EXP, FRAC> FloatBase<EXP,FRAC>::Build(i64 data)
{
    u64 exp, frac, ans, len;
    if(data < 0) 
    {
        ans |= 1 << (FRAC + EXP);
        data = std::abs(data);
    }

    len = 64 - __builtin_clzll(data);
    exp = len - 1 + BIAS;
    frac = doRound<FRAC>(data, &exp);
    ans |= exp << FRAC;
    ans |= frac;

    return FloatBase(&ans);
}

template<int EXP, int FRAC>
FloatBase<EXP, FRAC> FloatBase<EXP,FRAC>::Build(const Fraction &f)
{
    u64 ans = 0;
    u64 upper = f.getUpper(),
        lower = f.getLower();

    if(upper == 0) return FloatBase(&ans);
    if(__builtin_popcountll(lower) != 1) 
        throw std::runtime_error("Lower number must be 2^x");
    int sign = f.getSign();
    ans |= sign << (EXP + FRAC);

    /* deal with upper and lower */
    u64 times;
    u64 exp, frac;
    if(upper < lower)
    {
        times = lower / upper - (upper == 1 ? 1 : 0);
        int e = __builtin_clzll(times) - 64 + BIAS;
        if(e + FRAC < 0) ans = 0;
        else if (e <= 0) // denormalized
        {
            u64 mul = (1 << (FRAC + BIAS - 1)) / lower;
            exp = 0;
            frac = doRound<FRAC>(upper * mul, &exp, true);
            ans |= (exp << FRAC) | frac;
        }
        else
        {
            exp = e;
            frac = doRound<FRAC>(upper, &exp);
            ans |= (exp << FRAC) | frac;
        }
        return FloatBase(&ans);
    }
    else if (upper > lower)
    {
        times = upper / lower;
        exp = 64 - __builtin_clzll(times) + BIAS - 1;
        frac = doRound<FRAC>(upper, &exp);
        ans |= (exp << FRAC) | frac;
        return FloatBase(&ans);
    }
    else
    {
        ans = 1 - 2 * sign;
        return FloatBase(&ans);
    }
}

namespace std
{
    template<int _e, int _f>
        std::string to_string(const FloatBase<_e, _f> & fb)
        {
            return fb.to_string();
        }
}

#endif
