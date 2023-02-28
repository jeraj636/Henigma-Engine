#include "upodabljalnik.h"
void Upodabljalnik::zanka(Objekt *obj)
{
        glBindVertexArray(obj->VAO);
        glUseProgram(obj->shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Upodabljalnik::nastavi()
{
        io::izpis("nastavljeno", io::type::msg);
}