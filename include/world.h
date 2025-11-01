#ifndef WORLD_H
#define WORLD_H

#include <vector>

namespace World
{
    struct WorldLattice {
        std::vector<float> data;
        uint16_t width, height;
        float &at (uint16_t i, uint16_t j)
        {
            return data[i*width + j];
        }
    };

    void InitLattice (WorldLattice &lattice);
}

#endif