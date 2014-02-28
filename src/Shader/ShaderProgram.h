#include <iostream>
#include <fstream>

#include <OpenGL/gl3.h>
#include "Shader.h"

class ShaderProgram {
 public:
    ShaderProgram();

 public:
    void createProgram();
    void deleteProgram();

    bool addShader(Shader *shader);
    bool linkProgram();
    void useProgram();

    GLuint getProgramID();

 private:
    GLuint programID;
    bool linked;

};
