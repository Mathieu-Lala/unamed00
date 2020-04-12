/**
 * @file src/module/graphic/AbstractGLFW/Shader.hpp
 *
 */

#ifndef ABSTRACT_GLFW_SHADER_HPP_
# define ABSTRACT_GLFW_SHADER_HPP_

# include <string_view>
# include <iostream>

# include <glad/glad.h>

# include <utils/utils.hpp>
# include <config/cmake_config.hpp>

class Shader {
public:

    static GLuint loadShader(const std::string_view path, GLuint type)
    {
        auto shader = glCreateShader(type);
        auto source = getContentFile(path);
        auto raw = source.data();
        glShaderSource(shader, 1, &raw, nullptr);
        glCompileShader(shader);

        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char buffer[512];
            glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << buffer << std::endl;
            return 0;
        }

        return shader;
    }

    Shader() : m_program(-1) { }

    Shader(const std::string_view vertex, const std::string_view fragment)
    {
        this->open(vertex, fragment);
    }

    ~Shader()
    {
        this->close();
    }

    bool open(const std::string_view vertex, const std::string_view fragment)
    {
        this->close();

        auto vertexShader = loadShader(vertex, GL_VERTEX_SHADER);
        auto fragmentShader = loadShader(fragment, GL_FRAGMENT_SHADER);

        m_program = glCreateProgram();
        glAttachShader(m_program, vertexShader);
        glAttachShader(m_program, fragmentShader);
        glLinkProgram(m_program);

        int success = 0;
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if (!success) {
            char buffer[512];
            glGetProgramInfoLog(m_program, sizeof(buffer), nullptr, buffer);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << buffer << std::endl;
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return true;
    }

    void close()
    {
        if (m_program != -1) {
            glDeleteProgram(m_program);
            m_program = -1;
        }
    }

    void use()
    {
        glUseProgram(m_program);
    }

private:

    std::int64_t m_program;

};

#endif /* !ABSTRACT_GLFW_SHADER_HPP_ */
