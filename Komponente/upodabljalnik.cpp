#include "upodabljalnik.h"
void Upodabljalnik::zanka()
{
        glBindVertexArray(obj->VAO);
        glUseProgram(obj->shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Upodabljalnik::nastavi(Objekt *kaz)
{
        obj = kaz;
        io::izpis("nastavljeno", io::type::msg);
}