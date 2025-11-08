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
    void setPerspective (RenderState &render, float width, float height, float fov, float zn, float zf);
    void setView (RenderState &render, float x, float y, float z);
    void setViewport (RenderState &render, int x, int y, int width, int height);
}

#endif // RENDERER_H