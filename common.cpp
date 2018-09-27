#include "common.h"


std::string Fraction::to_string() const
{
    std::string ret{};
    if(sign) ret = "-";
    ret += std::to_string(upper);
    if(lower != 1)
       ret += "/" + std::to_string(lower);
    return ret;
}

using namespace std;
ostream &operator<<(ostream & o, const Fraction &f)
{
    o<<f.to_string();
    return o;
}

istream &operator>>(istream & i, Fraction &f)
{
    auto _pred = [](char c){return std::isdigit(c) || c=='-';};
    while(!_pred(i.peek())) i.get();
    u64 upper, lower;
    if(i.peek() == '-')
    {
        f.sign = 1; i.get();
    }
    i >> upper;
    if(i.peek() == '/') i.get();
    i >> lower;
    f.upper = upper; f.lower = lower; f.reduce();
    return i;
}

