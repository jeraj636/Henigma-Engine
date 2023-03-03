#include "upodabljalnik.h"
void Upodabljalnik::zanka()
{
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, okno->_texture);
        glUniform1i(_lokacijaTeksture, 0);
        glUniform4f(_lokacijaBarve, barvaObjekta.r, barvaObjekta.g, barvaObjekta.b, barvaObjekta.a);
        glBindVertexArray(okno->_VAO);
        // glUniform1i()
        glUseProgram(okno->_shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Upodabljalnik::nastavi(Objekt *kazObj, Okno *kazOkno)
{
        obj = kazObj;
        okno = kazOkno;
        io::izpis("upodabljalnik je nastavljen", io::type::msg);
        _lokacijaBarve = glGetUniformLocation(okno->_shaderProgram, "barva");
        _lokacijaTeksture = glGetUniformLocation(okno->_shaderProgram, "teks");
}
Upodabljalnik::Upodabljalnik()
    : barvaObjekta(0xff5500ff)
{
}
