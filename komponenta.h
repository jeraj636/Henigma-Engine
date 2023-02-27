#pragma once
#include "objekt.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ostalo.h"
class Neki
{
public:
    uint VAO, shaderProgram;
};
class Komponenta
{

public:
    // Objekt neki;
    virtual void nastavi() = 0;
    virtual void zanka(Neki *ptr) = 0;
    bool aktivno = 1;
};
class Upodabljalnik : public Komponenta
{

public:
    void nastavi() override
    {
        io::izpis("nastavljeno", io::type::msg);
    }
    void zanka(Neki *ptr) override
    {
        if (ptr != nullptr)
            io::izpis("nastavljeno", io::type::msg);
        // ptr->dobiIme();
        glBindVertexArray(ptr->VAO);
        glUseProgram(ptr->shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};
