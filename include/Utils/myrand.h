#ifndef MYRAND_H
#define MYRAND_H

#include <cstdint>

namespace MyRand
{
    struct RNG
    {
        uint32_t seed;
        uint32_t operator () ()
        {
            seed = seed * 1664525U + 1013904223U;
            return seed;
        }

        double getDouble ()
        {
            seed = seed * 1664525U + 1013904223U;
            return (float) seed / 4294967296.0f;
        }
    };
}

#endif