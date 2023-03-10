#include "transformacija.h"

void Transformacija::zanka()
{
        Mpozicija = glm::mat4(1);
        Mrotacija = glm::mat4(1);
        Mvelikost = glm::mat4(1);

        Mpozicija = glm::translate(Mpozicija, glm::vec3(pozicija.x, pozicija.y, pozicija.z));
        Mrotacija = glm::rotate(Mrotacija, glm::radians(rotacija.z), glm::vec3(0.0f, 0.0f, 1.0f));
        Mvelikost = glm::scale(Mvelikost, glm::vec3(velikost.x, velikost.y, velikost.z));
        glUniformMatrix4fv(_lokMrotacije, 1, GL_FALSE, &Mrotacija[0][0]);
        glUniformMatrix4fv(_lokMpozicije, 1, GL_FALSE, &Mpozicija[0][0]);
        glUniformMatrix4fv(_lokMvelikost, 1, GL_FALSE, &Mvelikost[0][0]);
}
void Transformacija::nastavi(Objekt *kazObj, Okno *kazOkno)
{
        obj = kazObj;
        okno = kazOkno;
        io::izpis("TRANSFORMATOR je nastavljen", io::type::msg);

        _lokMrotacije = glGetUniformLocation(okno->_shaderProgram, "Mrot");
        _lokMpozicije = glGetUniformLocation(okno->_shaderProgram, "Mpoz");
        _lokMvelikost = glGetUniformLocation(okno->_shaderProgram, "Mvel");
}
Transformacija::Transformacija()
    : matrica(1), Mpozicija(1), Mrotacija(1), Mvelikost(1)
{
        // JAOKB JE KUL
        pozicija.x = 0;
        pozicija.y = 0;
        pozicija.z = 0;

        rotacija.x = 0;
        rotacija.y = 0;
        rotacija.z = 0;

        velikost.x = 1;
        velikost.y = 1;
        velikost.z = 1;
}
