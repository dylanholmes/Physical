#include "Shader.h"

Shader::Shader() {
    shaderLoaded = false;
}

bool Shader::load(const char *filename, int shaderType) {
    using namespace std;

    /*---- Shader Read -----*/

    ifstream file;

    // file open
    file.open(filename);
    if (!file)
        return false;

    // file size
    file.seekg(0, file.end);
    int size = file.tellg();
    file.seekg(0, file.beg);

    // file read
    char *contents = new char[size+1];
    file.read(contents, size);
    contents[size] = '\0';  // don't forget a towel!

    // file close
    file.close();

    /*---- Shader Load -----*/

    // shader create
    GLuint shaderID = glCreateShader(shaderType);

    // shader source
    glShaderSource(shaderID, 1, new const char*(contents), NULL);

    // shader compile
    glCompileShader(shaderID);

    // shader verify
    int compilationStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus);
    if (compilationStatus == GL_FALSE)
        return false;

    /*---- Shader Save ----*/

    this->shaderID = shaderID;
    this->shaderType = shaderType;
    this->shaderLoaded = true;

    return this->shaderLoaded;
}

bool Shader::unload() {
    return !shaderLoaded;
}

bool Shader::isLoaded() {
    return shaderLoaded;
}

GLuint Shader::getShaderID() {
    if (!shaderLoaded)
        return 0;
    return shaderID;
}
