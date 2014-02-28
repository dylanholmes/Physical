#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    linked = false;
}

void ShaderProgram::createProgram() {
    programID = glCreateProgram();
}
void ShaderProgram::deleteProgram() {
    if(!linked)
        return;
    linked = false;
    glDeleteProgram(programID);
}

bool ShaderProgram::addShader(Shader *shader) {
    if(!shader->isLoaded())
        return false;

    glAttachShader(programID, shader->getShaderID());

    return true;
}
bool ShaderProgram::linkProgram() {
    // program link
    glLinkProgram(programID);
    // program verify
    int linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    return linked = (linkStatus == GL_TRUE);
}

void ShaderProgram::useProgram() {
    if(linked)
        glUseProgram(programID);
}

GLuint ShaderProgram::getProgramID() {
    return programID;
}
