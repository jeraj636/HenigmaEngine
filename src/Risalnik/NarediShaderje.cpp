#include "../../Include/Risalnik.h"
#include "../../Include/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <iostream>

void Risalnik::NarediShaderje()
{
    const char *vertexShaderSRC = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTekPos;

        out vec2 iTekPos;

        uniform mat4 uOrto;
        uniform mat4 uTrans;

        void main()
        {
            gl_Position = uOrto * uTrans * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
            iTekPos = aTekPos;
        }
    )";
    const char *fragmentShaderSRC = R"(
        #version 330 core

        out vec4 FragColor;

        in vec2 iTekPos;

        uniform sampler2D uTekID;
        uniform vec4 uBozd;
        uniform vec4 uBobj;

        void main()
        {
            FragColor = uBobj * texture(uTekID,iTekPos);
        }

    )";

    int uspeh;

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader, 1, &vertexShaderSRC, NULL);
    glCompileShader(m_vertexShader);

    glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
        std::cout << infoLog;
        io::err("NI VERTEX SHADERJA");
    }
    io::msg("VERTEX SHADER");

    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &fragmentShaderSRC, NULL);
    glCompileShader(m_fragmentShader);

    glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
        std::cout << infoLog;
        io::err("NI FRAGMENT SHADERJA");
    }
    io::msg("FRAGMENT SHADER");

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        io::err("NI SHADER PROGRAMA");
    io::msg("SHADER PROGRAM");

    glUseProgram(m_shaderProgram);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}

void Risalnik::NarediShaderjeB()
{
    const char *vertexShaderSRC = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTekPos;

        out vec2 iTekPos;

        uniform mat4 uOrto;
        uniform mat4 uTrans;

        void main()
        {
            gl_Position = uOrto * uTrans * vec4(aPos.x, aPos.y, aPos.z, 1.0f);            
            iTekPos = aTekPos;
        }
    )";
    const char *fragmentShaderSRC = R"(
        #version 330 core

        out vec4 FragColor;

        in vec2 iTekPos;

        uniform sampler2D uTekID;
        uniform vec4 uBozd;
        uniform vec4 uBobj;

        void main()
        {
            //FragColor = vec4(1.0f,1.0f,1.0f,texture(uTekID,iTekPos).r ) * uBobj;
            FragColor= vec4(1.0f,1.0f,1.0f,1.0f);
        }
    )";

    int uspeh;

    m_vertexShaderB = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderB, 1, &vertexShaderSRC, NULL);
    glCompileShader(m_vertexShaderB);

    glGetShaderiv(m_vertexShaderB, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_vertexShaderB, 512, NULL, infoLog);
        std::cout << infoLog;
        io::err("NI B VERTEX SHADERJA");
    }
    io::msg("B VERTEX SHADER");

    m_fragmentShaderB = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderB, 1, &fragmentShaderSRC, NULL);
    glCompileShader(m_fragmentShaderB);

    glGetShaderiv(m_fragmentShaderB, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_fragmentShaderB, 512, NULL, infoLog);
        std::cout << infoLog;
        io::err("NI B FRAGMENT SHADERJA");
    }
    io::msg("B FRAGMENT SHADER");

    m_shaderProgramB = glCreateProgram();
    glAttachShader(m_shaderProgramB, m_vertexShaderB);
    glAttachShader(m_shaderProgramB, m_fragmentShaderB);
    glLinkProgram(m_shaderProgramB);

    glGetProgramiv(m_shaderProgramB, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        io::err("NI B SHADER PROGRAMA");
    io::msg("B SHADER PROGRAM");

    glUseProgram(m_shaderProgramB);

    glDeleteShader(m_vertexShaderB);
    glDeleteShader(m_fragmentShaderB);
}