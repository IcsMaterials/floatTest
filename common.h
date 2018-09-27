#ifndef _COMMON_HH_
#define _COMMON_HH_

#include <stdint.h>
#include <string>
#include <utility>
#include <cassert>
#include <iostream>
#include <cctype>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef uint64_t u64;
typedef uint32_t u32;
typedef int32_t i32;
typedef int64_t i64;


class Fraction;

class Fraction
{
    private:
        u64 upper;
        u64 lower;
        int sign;
        
    private:
        inline u64 gcd(int a, int b)   //a is larger
        {
            int t;
            if(a < b) std::swap(a, b);
            while(a % b)
            {
                t = a;
                a = b;
                b = t % b;
            }
            return b;
        }
        inline void reduce()
        {
            if(upper == 0) return;
            assert(lower);
            auto g = gcd(upper, lower);
            upper /= g; lower /= g;
        }

    public:
        Fraction(int si=0, u64 up=0, u64 lo=1)
        {
            if(up == 0) 
            {
                upper = 0; lower = 1; sign = si; return;
            }
            assert(lo);
            auto g = gcd(up, lo);
            upper = up/g; lower = lo/g;
            sign = si;
        }

        inline u64 getUpper()const {return upper;}
        inline u64 getLower()const {return lower;}
        inline int getSign() const {return sign;}
        std::string to_string() const;

    public:
        inline bool operator<(const Fraction & r) const
        {
            return upper * r.lower < r.upper * lower;
        }
        inline bool operator==(const Fraction &r) const
        {
            return upper * r.lower == r.upper * lower;
        }

        friend std::ostream &operator<<(std::ostream &, const Fraction &);
        friend std::istream &operator>>(std::istream &i, Fraction &f);
};


#endif
