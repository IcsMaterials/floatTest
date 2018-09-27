#include <iostream>
#include "start.h"

void start(int exp, int frac);
int main()
{
#ifdef EXP
#ifdef FRAC
    CommandEngine<FloatBase<EXP,FRAC>>().Start();
    return 0;
#endif
#endif
    int exp, frac;
    std::cout<<"Input the format for floats please!"<<std::endl;
    std::cout<<"    Exp length: ";
    std::cin>>exp;
    std::cout<<"    Frac length: ";
    std::cin>>frac;
    std::cout<<std::endl;
    start(exp, frac);
    return 0;
}

