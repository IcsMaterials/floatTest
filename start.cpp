#include "start.h"
#include "engine.h"
#include "common.h"
#include "float.hpp"
void start(int exp, int frac){
    auto zip = [](int a,int b){return a << 6 | b;};
    int k = zip(exp, frac);
    switch (k) {
        case 65:
            CommandEngine<FloatBase<1, 1 >>().Start(); break;
        case 66:
            CommandEngine<FloatBase<1, 2 >>().Start(); break;
        case 67:
            CommandEngine<FloatBase<1, 3 >>().Start(); break;
        case 68:
            CommandEngine<FloatBase<1, 4 >>().Start(); break;
        case 69:
            CommandEngine<FloatBase<1, 5 >>().Start(); break;
        case 70:
            CommandEngine<FloatBase<1, 6 >>().Start(); break;
        case 71:
            CommandEngine<FloatBase<1, 7 >>().Start(); break;
        case 72:
            CommandEngine<FloatBase<1, 8 >>().Start(); break;
        case 73:
            CommandEngine<FloatBase<1, 9 >>().Start(); break;
        case 74:
            CommandEngine<FloatBase<1, 10 >>().Start(); break;
        case 75:
            CommandEngine<FloatBase<1, 11 >>().Start(); break;
        case 76:
            CommandEngine<FloatBase<1, 12 >>().Start(); break;
        case 77:
            CommandEngine<FloatBase<1, 13 >>().Start(); break;
        case 78:
            CommandEngine<FloatBase<1, 14 >>().Start(); break;
        case 129:
            CommandEngine<FloatBase<2, 1 >>().Start(); break;
        case 130:
            CommandEngine<FloatBase<2, 2 >>().Start(); break;
        case 131:
            CommandEngine<FloatBase<2, 3 >>().Start(); break;
        case 132:
            CommandEngine<FloatBase<2, 4 >>().Start(); break;
        case 133:
            CommandEngine<FloatBase<2, 5 >>().Start(); break;
        case 134:
            CommandEngine<FloatBase<2, 6 >>().Start(); break;
        case 135:
            CommandEngine<FloatBase<2, 7 >>().Start(); break;
        case 136:
            CommandEngine<FloatBase<2, 8 >>().Start(); break;
        case 137:
            CommandEngine<FloatBase<2, 9 >>().Start(); break;
        case 138:
            CommandEngine<FloatBase<2, 10 >>().Start(); break;
        case 139:
            CommandEngine<FloatBase<2, 11 >>().Start(); break;
        case 140:
            CommandEngine<FloatBase<2, 12 >>().Start(); break;
        case 141:
            CommandEngine<FloatBase<2, 13 >>().Start(); break;
        case 193:
            CommandEngine<FloatBase<3, 1 >>().Start(); break;
        case 194:
            CommandEngine<FloatBase<3, 2 >>().Start(); break;
        case 195:
            CommandEngine<FloatBase<3, 3 >>().Start(); break;
        case 196:
            CommandEngine<FloatBase<3, 4 >>().Start(); break;
        case 197:
            CommandEngine<FloatBase<3, 5 >>().Start(); break;
        case 198:
            CommandEngine<FloatBase<3, 6 >>().Start(); break;
        case 199:
            CommandEngine<FloatBase<3, 7 >>().Start(); break;
        case 200:
            CommandEngine<FloatBase<3, 8 >>().Start(); break;
        case 201:
            CommandEngine<FloatBase<3, 9 >>().Start(); break;
        case 202:
            CommandEngine<FloatBase<3, 10 >>().Start(); break;
        case 203:
            CommandEngine<FloatBase<3, 11 >>().Start(); break;
        case 204:
            CommandEngine<FloatBase<3, 12 >>().Start(); break;
        case 257:
            CommandEngine<FloatBase<4, 1 >>().Start(); break;
        case 258:
            CommandEngine<FloatBase<4, 2 >>().Start(); break;
        case 259:
            CommandEngine<FloatBase<4, 3 >>().Start(); break;
        case 260:
            CommandEngine<FloatBase<4, 4 >>().Start(); break;
        case 261:
            CommandEngine<FloatBase<4, 5 >>().Start(); break;
        case 262:
            CommandEngine<FloatBase<4, 6 >>().Start(); break;
        case 263:
            CommandEngine<FloatBase<4, 7 >>().Start(); break;
        case 264:
            CommandEngine<FloatBase<4, 8 >>().Start(); break;
        case 265:
            CommandEngine<FloatBase<4, 9 >>().Start(); break;
        case 266:
            CommandEngine<FloatBase<4, 10 >>().Start(); break;
        case 267:
            CommandEngine<FloatBase<4, 11 >>().Start(); break;
        case 321:
            CommandEngine<FloatBase<5, 1 >>().Start(); break;
        case 322:
            CommandEngine<FloatBase<5, 2 >>().Start(); break;
        case 323:
            CommandEngine<FloatBase<5, 3 >>().Start(); break;
        case 324:
            CommandEngine<FloatBase<5, 4 >>().Start(); break;
        case 325:
            CommandEngine<FloatBase<5, 5 >>().Start(); break;
        case 326:
            CommandEngine<FloatBase<5, 6 >>().Start(); break;
        case 327:
            CommandEngine<FloatBase<5, 7 >>().Start(); break;
        case 328:
            CommandEngine<FloatBase<5, 8 >>().Start(); break;
        case 329:
            CommandEngine<FloatBase<5, 9 >>().Start(); break;
        case 330:
            CommandEngine<FloatBase<5, 10 >>().Start(); break;
        case 385:
            CommandEngine<FloatBase<6, 1 >>().Start(); break;
        case 386:
            CommandEngine<FloatBase<6, 2 >>().Start(); break;
        case 387:
            CommandEngine<FloatBase<6, 3 >>().Start(); break;
        case 388:
            CommandEngine<FloatBase<6, 4 >>().Start(); break;
        case 389:
            CommandEngine<FloatBase<6, 5 >>().Start(); break;
        case 390:
            CommandEngine<FloatBase<6, 6 >>().Start(); break;
        case 391:
            CommandEngine<FloatBase<6, 7 >>().Start(); break;
        case 392:
            CommandEngine<FloatBase<6, 8 >>().Start(); break;
        case 393:
            CommandEngine<FloatBase<6, 9 >>().Start(); break;
        case 449:
            CommandEngine<FloatBase<7, 1 >>().Start(); break;
        case 450:
            CommandEngine<FloatBase<7, 2 >>().Start(); break;
        case 451:
            CommandEngine<FloatBase<7, 3 >>().Start(); break;
        case 452:
            CommandEngine<FloatBase<7, 4 >>().Start(); break;
        case 453:
            CommandEngine<FloatBase<7, 5 >>().Start(); break;
        case 454:
            CommandEngine<FloatBase<7, 6 >>().Start(); break;
        case 455:
            CommandEngine<FloatBase<7, 7 >>().Start(); break;
        case 456:
            CommandEngine<FloatBase<7, 8 >>().Start(); break;
        case 513:
            CommandEngine<FloatBase<8, 1 >>().Start(); break;
        case 514:
            CommandEngine<FloatBase<8, 2 >>().Start(); break;
        case 515:
            CommandEngine<FloatBase<8, 3 >>().Start(); break;
        case 516:
            CommandEngine<FloatBase<8, 4 >>().Start(); break;
        case 517:
            CommandEngine<FloatBase<8, 5 >>().Start(); break;
        case 518:
            CommandEngine<FloatBase<8, 6 >>().Start(); break;
        case 519:
            CommandEngine<FloatBase<8, 7 >>().Start(); break;
        case 577:
            CommandEngine<FloatBase<9, 1 >>().Start(); break;
        case 578:
            CommandEngine<FloatBase<9, 2 >>().Start(); break;
        case 579:
            CommandEngine<FloatBase<9, 3 >>().Start(); break;
        case 580:
            CommandEngine<FloatBase<9, 4 >>().Start(); break;
        case 581:
            CommandEngine<FloatBase<9, 5 >>().Start(); break;
        case 582:
            CommandEngine<FloatBase<9, 6 >>().Start(); break;
        case 641:
            CommandEngine<FloatBase<10, 1 >>().Start(); break;
        case 642:
            CommandEngine<FloatBase<10, 2 >>().Start(); break;
        case 643:
            CommandEngine<FloatBase<10, 3 >>().Start(); break;
        case 644:
            CommandEngine<FloatBase<10, 4 >>().Start(); break;
        case 645:
            CommandEngine<FloatBase<10, 5 >>().Start(); break;
        case 705:
            CommandEngine<FloatBase<11, 1 >>().Start(); break;
        case 706:
            CommandEngine<FloatBase<11, 2 >>().Start(); break;
        case 707:
            CommandEngine<FloatBase<11, 3 >>().Start(); break;
        case 708:
            CommandEngine<FloatBase<11, 4 >>().Start(); break;
        case 769:
            CommandEngine<FloatBase<12, 1 >>().Start(); break;
        case 770:
            CommandEngine<FloatBase<12, 2 >>().Start(); break;
        case 771:
            CommandEngine<FloatBase<12, 3 >>().Start(); break;
        case 833:
            CommandEngine<FloatBase<13, 1 >>().Start(); break;
        case 834:
            CommandEngine<FloatBase<13, 2 >>().Start(); break;
        case 897:
            CommandEngine<FloatBase<14, 1 >>().Start(); break;
        default: std::cout<<"Not support! "<<std::endl;break;}
}

