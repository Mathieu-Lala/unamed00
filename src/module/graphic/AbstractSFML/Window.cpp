/**
 * @file src/module/graphic/AbstractSFML/Window.cpp
 *
 */

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>

#include <config/cmake_config.hpp>
#include <data/Component.hpp>

#include "Window.hpp"

WindowSFML::WindowSFML()
{
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int vertexShader;
int fragmentShader;
int shaderProgram;

bool WindowSFML::init()
{
    sf::ContextSettings settings;
    settings.majorVersion = 4;
    settings.minorVersion = 5;
    settings.attributeFlags = sf::ContextSettings::Core | sf::ContextSettings::Debug;

    this->m_window.create(sf::VideoMode(1080, 720), "", sf::Style::Default, settings);
    this->m_window.setActive(true);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction));

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    glEnable(GL_TEXTURE_2D);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);


    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool WindowSFML::isRunning()
{
    return this->m_window.isOpen();
}

void WindowSFML::close()
{
    this->m_window.close();
}

void WindowSFML::setTitle(const std::string &title)
{
    this->m_window.setTitle(title);
}

void WindowSFML::setSize(unsigned int x, unsigned int y)
{
    this->m_window.setSize(sf::Vector2u(x, y));
}

bool WindowSFML::setFavicon(const std::string &filepath)
{
    sf::Image img;

    if (!img.loadFromFile(filepath))
        return false;

    this->m_window.setIcon(
        img.getSize().x, img.getSize().y,
        img.getPixelsPtr());

    return true;
}

void WindowSFML::render()
{
    this->m_window.display();
}

void WindowSFML::clear(unsigned int color)
{
    const float r = (color & 0xFF000000) / 255.0f;
    const float g = (color & 0x00FF0000) / 255.0f;
    const float b = (color & 0x0000FF00) / 255.0f;
    const float a = (color & 0x000000FF) / 255.0f;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //this->m_window.clear(sf::Color(color));
}

void WindowSFML::draw(const std::unique_ptr<ecs::World> &world)
{
    world->tickSystem<CShape>([this](CShape *shape) {

        float vertices[] = {
            shape->x + shape->w, shape->y + shape->h, 0.0f,
            shape->x + shape->w, shape->y,            0.0f,
            shape->x,            shape->y,            0.0f,
            shape->x,            shape->y + shape->h, 0.0f
        };

        unsigned int indices[] = {
            0, 1, 3, // first Triangle
            1, 2, 3  // second Triangle
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

    });
}

bool WindowSFML::pollEvent(graphic::Event &out)
{
    sf::Event e;
    if (!this->m_window.pollEvent(e))
        return false;

    if (e.type == sf::Event::Closed)
        out.type = graphic::Event::CLOSED;
    if (e.type == sf::Event::KeyPressed) {
        out.type = graphic::Event::KEY_PRESSED;
        out.key.code = static_cast<graphic::KeyBoard::Key>(e.key.code);
    }
    if (e.type == sf::Event::KeyReleased) {
        out.type = graphic::Event::KEY_RELEASED;
        out.key.code = static_cast<graphic::KeyBoard::Key>(e.key.code);
    }
    return true;
}

bool WindowSFML::takeScreenShot(const std::string &filepath)
{
    sf::Texture screen;
    screen.create(this->m_window.getSize().x, this->m_window.getSize().y);
    screen.update(this->m_window);
    const sf::Image img = screen.copyToImage();
    return img.saveToFile(filepath);
}
