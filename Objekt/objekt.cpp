#include "objekt.h"
#include "../Komponente/komponenta.h"
#include "../Render/render.h"
Objekt::Objekt(std::string ime)
{
    imeObjekta = ime;
}
void Objekt::nstk()
{
    tabKomponent.back()->nastavi(this /*nutzz*/, _okno);
}
void Objekt::nastavi(Okno *kaz)
{
    _okno = kaz;
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
