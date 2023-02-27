// #include "komponenta.h"
#include "objekt.h"

Objekt::Objekt(std::string ime)
{
    VAO = 0;
    _ime = ime;
    shaderProgram = 0;
}
inline void Objekt::nastavi()
{
    io::izpis("objekt je nastavljen", io::type::msg);
}
void Objekt::zanka(uint _VAO, uint _shaderProgram)
{
    for (int i = 0; i < tabKomponent.size(); i++)
    {
        nn.VAO = _VAO;
        nn.shaderProgram = _shaderProgram;
        if (tabKomponent[i]->aktivno)
            tabKomponent[i]->zanka(&nn);
    }
}
std::string Objekt::dobiIme()
{
    return _ime;
}