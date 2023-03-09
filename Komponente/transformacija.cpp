#include "transformacija.h"

void Transformacija::zanka()
{
        matrica = glm::mat4(1.0f);
        matrica = glm::translate(matrica, glm::vec3(pozicija.x, pozicija.y, pozicija.z));
        glUniformMatrix4fv(_lokMatrice, 1, GL_FALSE, &matrica[0][0]);
}
void Transformacija::nastavi(Objekt *kazObj, Okno *kazOkno)
{
        obj = kazObj;
        okno = kazOkno;
        io::izpis("TRANSFORMATOR je nastavljen", io::type::msg);

        _lokMatrice = glGetUniformLocation(okno->_shaderProgram, "matrica");
}
Transformacija::Transformacija()
    : matrica(1.0f) //, Mpoz(1.0f), Mvel(1.0f), Mrot(1.0f)
{
        // JAOKB JE KUL
}
