#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ostalo.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

// nastavi //zanka
class Objekt
{
public:
    Objekt(std::string ime)
    {
        _ime = ime;
    }
    void nastavi()
    {
        io::izpis("OBJEKT JE NASTAVLJEN", io::type::msg);
    }
    void zanka(uint shaderProgram, uint VAO)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    std::string dobiIme()
    {
        return _ime;
    }

private:
    std::string _ime;
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
class Scena
{
public:
    Scena()
        : _barvaOdzadja(0x00ffffff)
    {
    }
    void nastavi(int dolzinaOkna, int VisinaOkna, const char *naslovOkna)
    {
        if (!glfwInit())
            io::izpis("NI GLFWJA", io::type::error);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        okno = glfwCreateWindow(dolzinaOkna, VisinaOkna, naslovOkna, NULL, NULL);
        if (okno == NULL)
            io::izpis("NI OKNA", io::type::error);

        glfwMakeContextCurrent(okno);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            io::izpis("NI GLADA", io::type::error);
        glfwSetFramebufferSizeCallback(okno, posodobiVelikostOkna);

        float tocke[] =
            {
                1.0, 1.0, 0.0,
                1.0, -1.0, 0.0,
                -1.0, -1.0, 0.0,
                -1.0, 1.0, 0.0};
        int indeksi[] =
            {
                0, 1, 2,
                0, 2, 3};

        const char *vertexShaderS = R"(
            #version 330 core
            layout (location=0) in vec3 aPos;
            
            void main()
            {
                gl_Position=vec4(aPos,1);
            }
        )";
        const char *fragmentShaderS = R"(
            #version 330 core
            out vec4 FragColor;

            void main() 
            {
                FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);
            } 

        )";
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        glGenBuffers(1, &_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);

        glGenBuffers(1, &_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_STATIC_DRAW);

        int uspeh;
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(_vertexShader, 1, &vertexShaderS, NULL);
        glCompileShader(_vertexShader);
        glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &uspeh);
        if (!uspeh)
            io::izpis("NI VERTEX SHADERJA", io::type::msg);

        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(_fragmentShader, 1, &fragmentShaderS, NULL);
        glCompileShader(_fragmentShader);
        glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &uspeh);
        if (!uspeh)
            io::izpis("NI FRGAMENT SHADERJA", io::type::msg);

        _shaderProgram = glCreateProgram();
        glAttachShader(_shaderProgram, _vertexShader);
        glAttachShader(_shaderProgram, _fragmentShader);
        glLinkProgram(_shaderProgram);

        glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &uspeh);
        if (!uspeh)
            io::izpis("NI PROGRAMA", io::type::error);

        glDeleteShader(_vertexShader);
        glDeleteShader(_fragmentShader);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }
    void spremeniBarvo(Barva barva)
    {
        _barvaOdzadja = barva;
    }
    void dodajObljekt(const std::string &imeObjekta)
    {
        tabObjektov.push_back(new Objekt(imeObjekta));
    }
    Objekt *poisciObjekt(const std::string &imeObjekta)
    {
        for (int i = 0; i < tabObjektov.size(); i++)
        {
            if (imeObjekta == tabObjektov[i]->dobiIme())
                return tabObjektov[i];
        }
        return nullptr;
    }
    void zanka()
    {
        glClearColor(_barvaOdzadja.r, _barvaOdzadja.g, _barvaOdzadja.b, _barvaOdzadja.a);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < tabObjektov.size(); i++)
        {
            tabObjektov[i]->zanka(_shaderProgram, _VAO);
        }
        glfwSwapBuffers(okno);
    }
    GLFWwindow *okno;
    ~Scena()
    {
        glfwTerminate();
    }

private:
    std::vector<Objekt *> tabObjektov;
    Barva _barvaOdzadja;
    static void posodobiVelikostOkna(GLFWwindow *okno, int dolzina, int visina)
    {
        glViewport(0, 0, dolzina, visina);
    }
    static uint _VBO;
    static uint _VAO;
    static uint _EBO;
    static uint _vertexShader;
    static uint _fragmentShader;
    static uint _shaderProgram;
};

uint Scena::_VBO = 0;
uint Scena::_VAO = 0;
uint Scena::_EBO = 0;
uint Scena::_vertexShader = 0;
uint Scena::_fragmentShader = 0;
uint Scena::_shaderProgram = 0;
