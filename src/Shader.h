#pragma once

#ifndef _Shader
#define _Shader

#include <glad/glad.h>

#include <string>
#include <vector>

class Shader {
public:
    Shader(const std::string &, const std::string &);

    GLuint GetProgram() const {
        return Program;
    }

private:
    GLuint Program = glCreateProgram();

    static void Compile(const std::string &, GLuint, GLenum);
};


#endif
