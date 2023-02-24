#include "objekt.h"

Objekt::Objekt(std::string ime)
{
    _ime = ime;
    VAO = 0;
    shaderProgram = 0;
}
void Objekt::nastavi()
{
    io::izpis("objekt je nastavljen", io::type::msg);
}
void Objekt::zanka(uint shaderProgram, uint VAO)
{
    for (int i = 0; i < tabKomponent.size(); i++)
    {
        if (tabKomponent[i]->aktivno)
            tabKomponent[i]->zanka();
    }
}
std::string Objekt::dobiIme()
{
    return _ime;
}
void Objekt::poz()
{
    io::izpis("poz", io::type::msg);
}
