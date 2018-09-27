#include <iostream>
#include <iomanip>
#include <vector>

#include "float.hpp"
#include "engine.h"

inline void outTestHeader(const std::string &name)
{
    std::cout<< KGRN << "=== TEST "<<name<<" -- START ==="<< KNRM <<std::endl;
}

inline void outTestStatus(const std::string &name, bool pass = true)
{
    std::cout<< KCYN << "=== TEST "<<name<<" -- END === ";
    if(pass)
        std::cout<< KGRN << " === PASS! ===";
    else std::cout<< KRED << " === FAIL! ===";
    std::cout<<KNRM<<std::endl;
}

void testFloat8()
{
    outTestHeader("FLOAT8");
    for(uint8_t c = 0;c <= 254;c++)
    {
        float8 a(&c);
        std::cout<<std::to_string(a)<<std::endl;
    }

    uint8_t c = 255;
    float8 a(&c);
    std::cout<<std::to_string(a)<<std::endl;
    outTestStatus("FLOAT8");
}

void testFloat32()
{
    outTestHeader("FLOAT32");
    using float32 = FloatBase<8,23>;
    float f = 1.5;
    float32 a(&f);
    std::cout<<a<<std::endl;
    outTestStatus("FLOAT32");
}

void testBuild()
{
    outTestHeader("BUILD INTEGER");
    std::vector<u64> vec;
    for(int i=20;i<=40;i++)
        vec.push_back(i);
    std::cout<<"======= Test Build : "<<std::endl;
    for(auto data : vec)
        std::cout<<data<<" : "<<float8::Build(data)<<std::endl;
    outTestStatus("BUILD INTEGER");
}

void testFraction()
{
    outTestHeader("BUILD FRACTION");
    std::vector<Fraction> vec;
    for(int i=0;i<=32;i++) vec.emplace_back(i%2, i ,512);
    for(auto frac : vec)
    {
        float8 a = float8::Build(frac);
        std::cout<<a<<std::endl;
    }

    //using float32 = FloatBase<8,23>;
    Fraction f2(0,17,1);
    float8 a = float8::Build(f2);
    std::cout<<a<<std::endl;
    outTestStatus("BUILD FRACTION");
}

void testRandomEngine()
{
    outTestHeader("TEST RANDOM");
    RandomFloatEngine<float8> engine;
    for(int i=0;i<10;i++)
        std::cout<<engine.Next()<<std::endl;
    outTestStatus("TEST RANDOM");
}

void testEngine()
{
    outTestHeader("TEST ENGINE");
    CommandEngine<float8> engine;
    engine.Start();
    outTestStatus("TEST ENGINE");
}

void generateCode(int irange, int jrange, int total)
{
    auto zip = [](int a,int b){return a << 6 | b;};

    std::cout<<"void start(int exp, int frac){"<<std::endl;
    std::cout<<"auto zip = [](int a,int b){return a << 6 | b;};"<<std::endl;
    std::cout<<"int k = zip(exp, frac);"<<std::endl;
    std::cout<<"switch (k) {"<<std::endl;
    for(int i=1;i<=irange;i++)
        for(int j=1;j<=jrange;j++)
        {
            if(i + j >= total) continue;
            int k = zip(i,j);
            printf("case %d:\n", k);
            printf("CommandEngine<FloatBase<%d, %d >>().Start(); break;\n",
                    i,j);
        }
    printf("default: std::cout<<\"Not support! \"<<std::endl;break;");
    std::cout<<"}\n}"<<std::endl;
}
int main()
{
    //testFloat8();
    //testBuild();
    //testFraction();
    //testRandomEngine();
    testEngine();
    //generateCode(15, 15, 16);
}
