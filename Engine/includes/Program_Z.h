#ifndef PROGRAM_Z_H
#define PROGRAM_Z_H

#include <stdint.h>
#include <Console_Z.h>

struct Global_Z{
    unsigned int unk1;
    unsigned int unk2;
    Console_Z* Cons;
};

extern Global_Z gData;

#endif