#include "Shader.h"
#include "FileReader.h"

Shader::Shader(const std::string &VertexShader, const std::string &FragmentShader) {
    Shader::Compile(VertexShader, Program, GL_VERTEX_SHADER);
    Shader::Compile(FragmentShader, Program, GL_FRAGMENT_SHADER);

    glLinkProgram(Program);

    GLint status = GL_FALSE;
    glGetProgramiv(Program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        GLint length = 0;
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &length);

        std::vector<GLchar> infoLog(length);
        glGetProgramInfoLog(Program, length, &length, &infoLog[0]);

        fprintf(stderr, "Error: %s", &infoLog[0]);
    }
}

void Shader::Compile(const std::string &File, GLuint Program, GLenum Type) {
    GLuint shader = glCreateShader(Type);

    std::string source = FileReader::Read(File)
            .ToString().Utf8Value();

    const char *data = source.c_str();
    glShaderSource(shader, 1, &data, nullptr);

    glCompileShader(shader);

    GLint status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        std::vector<GLchar> description(length);
        glGetShaderInfoLog(shader, length, &length, &description[0]);

        fprintf(stderr, "(%s) GL %s", File.c_str(), &description[0]);
    }

    glAttachShader(Program, shader);
    glDeleteShader(shader);
}
