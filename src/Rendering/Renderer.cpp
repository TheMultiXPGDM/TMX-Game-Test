#include "Utils/errorMsg.h"
#include "Rendering/Renderer.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>

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

    void setPerspective (RenderState &render, float width, float height, float fov, float zf, float zn) {
        glMatrixMode(GL_PROJECTION);
        glm::mat4 proj = glm::perspectiveFov(fov, width, height, zn, zf);
        glLoadMatrixf((GLfloat *) &proj);
    }

    void setViewport (RenderState &render, int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }

    void setView (RenderState &render, float x, float y, float z)
    {
        glMatrixMode(GL_MODELVIEW);
        glm::mat4 view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glLoadMatrixf((GLfloat *) &view);
    }
}