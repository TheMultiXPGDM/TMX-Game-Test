#include "world.h"

#include "Utils/noise.h"

namespace World {

    void InitLattice (WorldLattice &lattice)
    {
        lattice.data.resize(lattice.width * lattice.height);

        uint16_t minDim = (lattice.width < lattice.height) ? lattice.width : lattice.height; 

        for (uint16_t i = 0; i < lattice.width; ++i)
        {
            float x = (float) i / minDim;
            for (uint16_t j = 0; j < lattice.height; ++j)
            {
                float y = (float) j / minDim;
                lattice.at(i,j) = Noise::fractalPerlin(glm::vec2(x,y)) * 0.5f + 0.5f;
            }
        }
    }
}