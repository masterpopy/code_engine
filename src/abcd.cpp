#include "cppdefines.h"

struct exzample{
    pokemon poke_sggg;

     void test_function2(){
        poke_sggg.moves[0] = 12;
    }
} exzample1;


extern "C" void test_function1(){
    exzample1.poke_sggg.current_hp=0;
    exzample1.poke_sggg.level = 0;

    exzample1.poke_sggg.iv_hp=3;
}