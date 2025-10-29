#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <yyjson.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>

#ifdef _WIN32
    #include <windows.h>
#endif

int width = 1280;
int height = 720;
bool fullscreen = false;
bool vsync = true;

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
    // pop up error message box if Windows is used
    #ifdef _WIN32
        MessageBox(NULL, description, "Error", MB_OK | MB_ICONERROR);
    #endif
}

glm::vec3 yuv2rgb(float y, float u, float v) {
    float r = y + 1.402f * v;
    float g = y - 0.34414f * u - 0.71414f * v;
    float b = y + 1.772f * u;
    return glm::vec3(r, g, b);
}

void writeConfigFile ()
{
    // config.json

    yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
    yyjson_mut_val *root = yyjson_mut_obj(doc);
    yyjson_mut_doc_set_root(doc, root);

    // ---------------------------------------------------------------------
    // create Graphics section
    yyjson_mut_val *graphics = yyjson_mut_obj(doc);
    yyjson_mut_obj_add(root, yyjson_mut_str(doc, "graphics"), graphics);

    // create Window configs

    // create Window section
    yyjson_mut_val *window = yyjson_mut_obj(doc);
    yyjson_mut_obj_add(graphics, yyjson_mut_str(doc, "window"), window);

    // Window size
    yyjson_mut_val *size = yyjson_mut_obj(doc);
    yyjson_mut_obj_add(window, yyjson_mut_str(doc, "size"), size);
    yyjson_mut_obj_add(size, yyjson_mut_str(doc, "width"), yyjson_mut_int(doc, width));
    yyjson_mut_obj_add(size, yyjson_mut_str(doc, "height"), yyjson_mut_int(doc, height));

    // Window Fullscreen
    yyjson_mut_obj_add(window, yyjson_mut_str(doc, "fullscreen"), yyjson_mut_bool(doc, fullscreen));

    // Window vsync
    yyjson_mut_obj_add(window, yyjson_mut_str(doc, "vsync"), yyjson_mut_bool(doc, vsync));


    // ---------------------------------------------------------------------
    // create Network section
    yyjson_mut_val *network = yyjson_mut_obj(doc);
    yyjson_mut_obj_add(root, yyjson_mut_str(doc, "network"), network);

    // STUN Server list
    yyjson_mut_val *stun = yyjson_mut_arr(doc);
    yyjson_mut_obj_add(network, yyjson_mut_str(doc, "stun"), stun);
    
    // ---------------------------------------------------------------------

    // write to file
    FILE *f;
    fopen_s(&f, "config.json", "w");
    if (f) {
        const char *json = yyjson_mut_write(doc, YYJSON_WRITE_PRETTY, NULL);
        fwrite(json, strlen(json), 1, f);
        fclose(f);
    }
}

bool readConfigFile () {

    // config.json
    // try to read config file

    yyjson_doc *doc = yyjson_read_file("config.json", 0, NULL, NULL);
    
    if (!doc) {
        return false;
    }

    yyjson_val *root = yyjson_doc_get_root(doc);

    yyjson_val *graphics = yyjson_obj_get(root, "graphics");
    yyjson_val *window = yyjson_obj_get(graphics, "window");

    yyjson_val *size = yyjson_obj_get(window, "size");
    width = (int) yyjson_get_uint(yyjson_obj_get(size, "width"));
    height = (int) yyjson_get_uint(yyjson_obj_get(size, "height"));

    fullscreen = yyjson_get_bool(yyjson_obj_get(window, "fullscreen"));
    vsync = yyjson_get_bool(yyjson_obj_get(window, "vsync"));

    yyjson_doc_free(doc);

    return true;
}

int main () {
    // robust initialization
    glfwSetErrorCallback(error_callback);

    // initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Error: GLFW initialization failed\n");
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    if (!readConfigFile())
        writeConfigFile();

    // create GLFW window
    GLFWwindow* window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Error: GLFW window creation failed\n");
        glfwTerminate();
        return -1;
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

    // initialize GLAD
    if (!gladLoadGL()) {
        fprintf(stderr, "Error: GLAD initialization failed\n");
        glfwTerminate();
        return -1;
    }

    // vsync
    glfwSwapInterval(vsync);

    // fullscreen
    if (fullscreen)
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, width, height, GLFW_DONT_CARE);

    // enable vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);

    const int SAMPLES = 8;

    float vertices[SAMPLES * 2];

    for (int i = 0; i < SAMPLES; ++i) {
        float ang = ((float) i / (float) SAMPLES) * 2.0f * 3.14159f;
        vertices[i * 2] = cos(ang);
        vertices[i * 2 + 1] = sin(ang);
    }

    // loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // set viewport to match window size
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        // render
        float ftime = (float) glfwGetTime();
        // clear the framebuffer
        glClear(GL_COLOR_BUFFER_BIT);
        // dark cornflower blue
        glClearColor(0.195f, 0.325f, 0.525f, 1.0f);

        // set projection
        glMatrixMode(GL_PROJECTION);
        float ratio = (float) width / (float) height;
        glm::mat4 projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
        glLoadMatrixf((const GLfloat*) &projection);
        
        // draw red circle
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // rotate given time
        glRotatef(ftime * 50.0f, 0.0f, 0.0f, 1.0f);
        glScalef(0.5f, 0.5f, 1.0f);
        glTranslatef(cos(-ftime * 2.0f) * 0.5f, sin(-ftime * 2.0f) * 0.5f, 0.0f);
        glm::vec3 color = yuv2rgb(0.5f, cos(ftime) * 0.25f, sin(ftime) * 0.25f);
        glColor3f(color.x, color.y, color.z);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, SAMPLES);

        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and process events
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}