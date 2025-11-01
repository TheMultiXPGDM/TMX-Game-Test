#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

namespace Renderer {
    struct RenderState
    {
        
    };

    bool init (RenderState &render);
    void clearColor (RenderState &render, float r, float g, float b, float a);
    void drawCircle (RenderState &render, float x, float y, float r);
}

#endif // RENDERER_H