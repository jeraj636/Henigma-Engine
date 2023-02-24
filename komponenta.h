#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
// #include "render.h"
#include "ostalo.h"
#include "objekt.h"
class Komponenta
{

public:
    virtual void nastavi() = 0;
    virtual void zanka(Objekt *objekt) = 0;
    bool aktivno = 1;
    Objekt *_objekt;
};

class Upodabljalnik : public Komponenta
{
public:
    void nastavi() override
    {
        io::izpis("upodabljalnik je nastavljen", io::type::msg);
    }
    void zanka(Objekt *objekt) override
    {
        glBindVertexArray(_objekt->VAO);
        glUseProgram(_objekt->shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};
