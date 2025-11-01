#ifndef NOISE_H
#define NOISE_H

#include <glm/glm.hpp>

namespace Noise
{
    inline glm::vec2 hash22 (glm::vec2 p)
    {
        p = glm::vec2(
            glm::dot(p, glm::vec2(123.456f, 456.789f)),
            glm::dot(p, glm::vec2(456.789f, 789.123f))
        );
        return glm::fract(glm::sin(p)*4567.891f);
    }

    inline float perlin (glm::vec2 p)
    {
        const float K1 = 0.36602540378f;
        const float K2 = 0.2113248654f;
        glm::vec2 i = glm::floor(p + (p.x + p.y) * K1);
        glm::vec2 a = p - i + (i.x + i.y) * K2;
        float m = glm::step(a.y, a.x);
        glm::vec2 o = glm::vec2(m, 1.0f - m);
        glm::vec2 b = a - o + K2;
        glm::vec2 c = a - 1.0f + 2.0f * K2;
        glm::vec3 h = max(0.5f - glm::vec3(glm::dot(a,a), glm::dot(b,b), glm::dot(c,c)), 0.0f);
        glm::vec3 n = h*h*h*h*glm::vec3(glm::dot(a,hash22(i) * 2.0f - 1.0f), glm::dot(b,hash22(i+o) * 2.0f - 1.0f), glm::dot(c,hash22(i+1.0f) * 2.0f - 1.0f));
        return dot(n, glm::vec3(70.0f));
    }

    inline float fractalPerlin (glm::vec2 p, float lacunarity = 2.0f, int samples = 8)
    {
        float value = 0.0f;
        float scale = lacunarity;
        for (float i = 0; i < samples; i += 1.0f)
        {
            value += perlin(p * scale) / scale;
            scale *= lacunarity;
        }
        return value;
    }
}

#endif