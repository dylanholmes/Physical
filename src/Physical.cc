#include "Physical.h"
#include <iostream>

/*
TODO:
  - Add names to particles??

  - Forces and particles as a (doubly) linked list ????

  - Structs to Classes -- performance?? (ParticleFactory to Particle and
	  ParticleSystem objects)
  
  - Initial position functions -> (hollow solid) square, circle, triangle

  - Accept array of positions and velocites as parameters

  - Memory Management

  - Inverse square forces

  - Inheritance among forces

  - Additional step functions (1/2 step method etc)

  - Save data to file for MATLAB

  - Simplify parameters to be simple file, to be loaded and run

  - Add Colormap

*/

Physical::Physical(System s) {
  int i;
  ScreenWidth = 600;
  ScreenHeight = 600;

  thisTime = 0.0;
  lastTime = 0.0;
  deltaTime = 0.0;

  done = false;


  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_ShowCursor(0);

  // Set up SDL Window to have an OpenGL 3.3 context

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  window = SDL_CreateWindow("Physical, let's get it", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight,
    SDL_WINDOW_OPENGL);

  screen = SDL_GetWindowSurface(window);

  // OpenGL

  // System Data
  this->system = s;
  // setupFor2();
  // setupFor100();
  // setupForSpringBox(10, 100000, 0.1, 0.1);
  // setupForFoldedSpringChain(5, 0.02, 100000, 1000, 0.02);


  // OpenGL Data
  glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
  glPointSize(5);

  ParticleSystem *ps = system.getParticleSystem();

  float positions[ps->n*3];
  for (i = 0; i < ps->n*3; i++)
    positions[i] = ps->p[i/3]->x[i % 3];

  glGenVertexArrays(1, uiVAO);
  glGenBuffers(1, uiVBO);

  glBindVertexArray(uiVAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STREAM_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Shaders

  vertexShader.load("./Shaders/SimpleVertexShader.vertexshader",
    GL_VERTEX_SHADER);
  fragmentShader.load("./Shaders/SimpleFragmentShader.fragmentshader",
    GL_FRAGMENT_SHADER);

  program.createProgram();
  assert(program.addShader(&vertexShader) == true);
  assert(program.addShader(&fragmentShader) == true);
  assert(program.linkProgram() == true);
  program.useProgram();
}

Physical::~Physical() {
  SDL_Quit();
}



void Physical::MainLoop() {
  while (!done) {
    Poll();
    Update();
    Render();
  }
}

void Physical::Poll() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            done = true;
        if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_ESCAPE)
                done = true;
    }
}

void Physical::Update() {
  int i;

  // Calculate deltaTime
  lastTime = thisTime;
  thisTime = SDL_GetTicks();
  deltaTime = (thisTime - lastTime) / 100000.0;

  ParticleSystem *ps = system.getParticleSystem();


  // System step
  system.eulerStep(deltaTime);

  // Update OpenGL Data
  float positions[ps->n*3];
  for (i = 0; i < ps->n*3; i++)
      positions[i] = ps->p[i/3]->x[i % 3];

  glBindVertexArray(uiVAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Physical::Render() {
  // We just clear color
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(uiVAO[0]);
  glDrawArrays(GL_POINTS, 0, system.getParticleSystem()->n);

  SDL_GL_SwapWindow(window);
}
