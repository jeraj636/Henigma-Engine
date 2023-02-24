#ifndef RENDER_H
#define RENDER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ostalo.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "objekt.h"

class Okno
{
public:
    Okno();
    void nastavi(int dolzinaOkna, int VisinaOkna, const char *naslovOkna);
    void spremeniBarvo(Barva barva);
    void dodajObljekt(const std::string &imeObjekta);
    Objekt *poisciObjekt(const std::string &imeObjekta);
    void zanka();
    GLFWwindow *okno;
    ~Okno();

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

#endif
