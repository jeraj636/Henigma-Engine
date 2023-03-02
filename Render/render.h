#ifndef RENDER_H
#define RENDER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "../Ostalo/ostalo.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
// #include "../Objekt/objekt.h"
//  class Objekt;
#include "../Objekt/scena.h"
class Scena;
class Okno
{
public:
    Okno();
    void unici(Scena *kateraScena);
    void nastavi(int dolzinaOkna, int VisinaOkna, const char *naslovOkna);
    void spremeniBarvo(Barva barva);
    void dodajSceno(const std::string &imeScene);
    Scena *poisciSceno(const std::string &imeScene);
    void zanka();
    GLFWwindow *okno;
    ~Okno();

    std::vector<Scena *> tabScen;
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
