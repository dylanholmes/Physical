#include <iostream>
#include <fstream>

#include <OpenGL/gl3.h>


class Shader {
 public:
    Shader();

 public:
    bool load(const char *filename, int shaderType);
    bool unload();

    bool isLoaded();
    GLuint getShaderID();

 private:
    GLuint shaderID;
    int shaderType;
    bool shaderLoaded;
};
