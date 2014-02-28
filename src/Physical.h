#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <assert.h>
#include <SDL2/SDL.h>
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "System/Particle.h"
#include "Shader/ShaderProgram.h"
#include "System/System.h"

#include "System/Force.h"

class Physical {
 public:
    explicit Physical(System system);
    ~Physical();

    void MainLoop();

    void Poll();
    void Update();
    void Render();

 private:
    int ScreenWidth;
    int ScreenHeight;

    bool done;

    double thisTime;
    double lastTime;
    double deltaTime;

    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Event event;

 private:
    GLuint uiVBO[1];
    GLuint uiVAO[1];
    GLuint VertexArrayID;
    GLuint vertexbuffer;

    Shader vertexShader;
    Shader fragmentShader;
    ShaderProgram program;

    System system;
};


#endif
