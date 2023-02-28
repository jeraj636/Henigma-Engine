// #include "komponenta.h"
#include "objekt.h"
#include "komponenta.h"
Objekt::Objekt(std::string ime)
{
    VAO = 0;
    _ime = ime;
    shaderProgram = 0;
}
void Objekt::nstk()
{
    tabKomponent.back()->nastavi();
}
inline void Objekt::nastavi()
{
    io::izpis("objekt je nastavljen", io::type::msg);
}
void Objekt::zanka(uint _VAO, uint _shaderProgram)
{
    for (int i = 0; i < tabKomponent.size(); i++)
    {

        shaderProgram = _shaderProgram;
        VAO = _VAO;
        if (tabKomponent[i]->aktivno)
            tabKomponent[i]->zanka(this);
    }
}
std::string Objekt::dobiIme()
{
    return _ime;
}