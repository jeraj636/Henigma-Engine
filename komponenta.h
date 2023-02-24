#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ostalo.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
class Komponenta
{

public:
    virtual void nastavi() = 0;
    virtual void zanka() = 0;
    bool aktivno = 1;
};
class Upodabljalnik : public Komponenta
{
public:
    void nastavi() override
    {
        io::izpis("upodabljalnik je nastavljen", io::type::msg);
    }
    void zanka() override
    {
        io::izpis("zanka", io::type::msg);
        /*
        glBindVertexArray(objekt->VAO);
        glUseProgram(objekt->shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        */
    }
};