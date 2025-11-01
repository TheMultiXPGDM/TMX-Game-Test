#include "Utils/errorMsg.h"
#include "Rendering/Renderer.h"

#include <cmath>

namespace Renderer
{
    bool init (RenderState &render)
    {
        glEnableClientState(GL_VERTEX_ARRAY);

        return true;
    }

    void clearColor (RenderState &render, float r, float g, float b, float a)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(r, g, b, a);
    }

    void drawCircle (RenderState &render, float x, float y, float r)
    {
        float vertices[32 * 2];

        for (int i = 0; i < 32; ++i)
        {
            float angle = (float) i / 32.0f * 2.0f * 3.14159f;
            vertices[i * 2] = x + r * cos(angle);
            vertices[i * 2 + 1] = y + r * sin(angle);
        }

        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 32);
    }
}