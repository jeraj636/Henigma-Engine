#include "objekt.h"
#include "../Komponente/komponenta.h"
#include "../Render/render.h"
Objekt::Objekt(std::string ime)
{
    VAO = 0;
    _ime = ime;
    shaderProgram = 0;
}
void Objekt::nstk()
{
    tabKomponent.back()->nastavi(this /*nutzz*/, _okno);
}
void Objekt::nastavi(Okno *kaz)
{
    _okno = kaz;
    VAO = kaz->_VAO;
    shaderProgram = kaz->_shaderProgram;
    io::izpis("objekt je nastavljen", io::type::msg);
}
void Objekt::zanka()
{
    for (int i = 0; i < tabKomponent.size(); i++)
    {
        if (tabKomponent[i]->aktivno)
            tabKomponent[i]->zanka();
    }
}
Objekt::~Objekt()
{
    for (int i = 0; i < tabKomponent.size(); i++)
        delete tabKomponent[i];
}
std::string Objekt::dobiIme()
{
    return _ime;
}
