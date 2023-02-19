#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ostalo.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Vec3
{
public:
    float x, y, z;
};

class Barva
{
public:
    float r, g, b, a;
    Barva(int hexCode)
    {
        a = hexCode & 0x000000ff;
        hexCode >>= 8;
        b = hexCode & 0x0000ff;
        hexCode >>= 8;
        g = hexCode & 0x00ff;
        hexCode >>= 8;
        r = hexCode & 0xff;
        a /= 0xff;
        r /= 0xff;
        g /= 0xff;
        b /= 0xff;
    }
};
class Okno
{
public:
    int Sirina, Visina;
    Okno(int sirina, int visina)
    {
        Sirina = sirina;
        Visina = visina;
        if (!glfwInit())
            io::izpis("ni glfw-ja", io::type::error);
        io::izpis("glfw deluje", io::type::msg);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        okno = glfwCreateWindow(sirina, visina, "Hacker Hen Script Maker - HHSM", NULL, NULL);
        if (okno == NULL)
        {
            io::izpis("ni okna", io::type::error);
            glfwTerminate();
        }
        io::izpis("okno deluje", io::type::msg);
        glfwMakeContextCurrent(okno);
        glfwSwapInterval(1);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            io::izpis("ni glada", io::type::error);
        io::izpis("glad deljue", io::type::msg);
        glfwSetFramebufferSizeCallback(okno, frameBufferSizeCallBack);
        io::izpis("vse dela", io::type::msg);
    }
    bool aliMoramZapreti()
    {
        return glfwWindowShouldClose(okno);
    }
    void pobarvaj(Barva barva)
    {
        glClearColor(barva.r, barva.g, barva.b, barva.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void osvezi()
    {
        glfwSwapBuffers(okno);
        glfwPollEvents();
    }
    ~Okno()
    {
        glfwTerminate();
    }
    int BeriInput()
    {
        if (glfwGetKey(okno, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            io::izpis("KONEC PROGRAMA!", io::type::msg);
            glfwSetWindowShouldClose(okno, true);
        }
        if (glfwGetKey(okno, GLFW_KEY_UP))
            return 1;
        if (glfwGetKey(okno, GLFW_KEY_DOWN))
            return 2;
        return 0;
    }

    GLFWwindow *okno;

private:
    static void frameBufferSizeCallBack(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

class GameObject
{
public:
    Vec3 pozicija;
    Vec3 velikost;
    Vec3 rotacija;
    GameObject(int visinaOkna, int sirinaOkna)
        : _barvaObjekta(0xffffff)
    {
        pozicija.x = 0;
        pozicija.y = 0;
        pozicija.z = 0;
        velikost.x = 0;
        velikost.y = 0;
        velikost.z = 0;
        rotacija.x = 0;
        rotacija.y = 0;
        rotacija.z = 0;
        // for (int i = 0; i < 12; i += 3)
        //{
        //   _tocke[i] /= sirinaOkna;
        //  _tocke[i + 1] /= visinaOkna;
        //}
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        glGenBuffers(1, &_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indeksi), _indeksi, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_tocke), _tocke, GL_DYNAMIC_DRAW);
        int succes;
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(_vertexShader, 1, &_vertexShaderSource, NULL);
        glCompileShader(_vertexShader);

        glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &succes);
        char log[512];
        if (!succes)
        {
            glGetShaderInfoLog(_vertexShader, 512, NULL, log);
            for (int i = 0; i < 512; i++)
                std::cout << log[i];
            io::izpis("ni vertex shaderja", io::type::error);
        }
        io::izpis("vertex shader deluje", io::type::msg);

        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(_fragmentShader, 1, &_fragmentShaderSource, NULL);
        glCompileShader(_fragmentShader);
        glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &succes);

        if (!succes)
            io::izpis("ni fragment shaderja", io::type::error);
        io::izpis("fragment shader deluje", io::type::msg);

        _shaderProgram = glCreateProgram();
        glAttachShader(_shaderProgram, _vertexShader);
        glAttachShader(_shaderProgram, _fragmentShader);
        glLinkProgram(_shaderProgram);
        glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &succes);
        if (!succes)
            io::izpis("ni shader programa", io::type::error);
        io::izpis("shader program deluje", io::type::msg);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        _lokPozicija = glGetUniformLocation(_shaderProgram, "transform");
        _lokRotacija = glGetUniformLocation(_shaderProgram, "rotacija");
        _lokVelikost = glGetUniformLocation(_shaderProgram, "povecava");
        _lokBarva = glGetUniformLocation(_shaderProgram, "bb");
        _vleikost = glm::mat4(1);
        _rotacija = glm::mat4(1);
        _pozicija = glm::mat4(1);
    }
    void narisiMe(int visina, int dolzina)
    {
        pozicija.x / dolzina;
        pozicija.y / visina;
        velikost.x / dolzina;
        velikost.y / visina;
        premakniMe(pozicija);
        spremeniMiVelikost(velikost);
        obrniMe(rotacija);
        glUniform3f(_lokBarva, _barvaObjekta.r, _barvaObjekta.g, _barvaObjekta.b);
        glUniformMatrix4fv(_lokPozicija, 1, GL_FALSE, glm::value_ptr(_pozicija));
        glUniformMatrix4fv(_lokRotacija, 1, GL_FALSE, glm::value_ptr(_rotacija));
        glUniformMatrix4fv(_lokVelikost, 1, GL_FALSE, glm::value_ptr(_vleikost));
        glUseProgram(_shaderProgram);
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        _vleikost = glm::mat4(1);
        _rotacija = glm::mat4(1);
        _pozicija = glm::mat4(1);
    }

    void spremeniMiBarvo(Barva b)
    {
        _barvaObjekta = b;
    }

private:
    void premakniMe(Vec3 KateraOs)
    {
        _pozicija = glm::mat4(1);
        _pozicija = glm::translate(_pozicija, glm::vec3(KateraOs.x / 1000, KateraOs.y / 1000, KateraOs.z / 1000));
    }
    void spremeniMiVelikost(Vec3 KateraOs)
    {
        _vleikost = glm::mat4(1);
        _vleikost = glm::scale(_vleikost, glm::vec3(KateraOs.x / 1000, KateraOs.y / 1000, KateraOs.z / 1000));
    }
    void obrniMe(Vec3 KateraOs)
    {
        _rotacija = glm::mat4(1);
        float kot;
        if (KateraOs.x != 0)
        {
            kot = KateraOs.x;
            _rotacija = glm::rotate(_rotacija, glm::radians(kot), glm::vec3(1, 0, 0));
        }
        if (KateraOs.y != 0)
        {
            kot = KateraOs.y;
            _rotacija = glm::rotate(_rotacija, glm::radians(kot), glm::vec3(0, 1, 0));
        }
        if (KateraOs.z != 0)
        {
            kot = KateraOs.z;
            _rotacija = glm::rotate(_rotacija, glm::radians(kot), glm::vec3(0, 0, 1));
        }
    }
    Barva _barvaObjekta;
    float _tocke[12] =
        {
            1, 1, 0.0,
            1, -1, 0.0,
            -1, -1, 0.0,
            -1, 1, 0.0};
    unsigned int _indeksi[6] = {0, 1, 3, 1, 2, 3};
    static unsigned int _VAO, _VBO, _EBO, _vertexShader, _fragmentShader;
    unsigned int _shaderProgram;
    unsigned int _lokRotacija, _lokPozicija, _lokVelikost, _lokBarva;
    glm::mat4 _vleikost = glm::mat4(1);
    glm::mat4 _rotacija = glm::mat4(1);
    glm::mat4 _pozicija = glm::mat4(1);
    static const char *_fragmentShaderSource;
    static const char *_vertexShaderSource;
};
unsigned int GameObject::_VAO = -1;
unsigned int GameObject::_vertexShader = -1;
unsigned int GameObject::_fragmentShader = -1;
unsigned int GameObject::_EBO = -1;
unsigned int GameObject::_VBO = -1;
const char *GameObject::_vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 transform;
uniform mat4 rotacija;
uniform mat4 povecava;
void main()
{
        gl_Position = transform*rotacija*povecava*vec4(aPos, 1.0);
}
        )";

const char *GameObject::_fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 bb;
void main()
{
    FragColor =vec4(bb,1);
} 
	)";
