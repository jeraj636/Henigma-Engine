#include "scena.h"

Scena::Scena(std::string _ime)
{
    ime = _ime;
}
void Scena::nastavi(Okno *oknoKaz)
{
    okno = oknoKaz;
}
void Scena::zanka()
{
    for (int i = 0; i < tabObjektov.size(); i++)
    {
        if (tabObjektov[i]->aktivno)
            tabObjektov[i]->zanka();
    }
}
Objekt *Scena::dodajObjekt(std::string ime)
{
    tabObjektov.push_back(new Objekt(ime));
    tabObjektov.back()->nastavi(okno);
    return tabObjektov.back();
}
Objekt *Scena::poisciObjekt(std::string ime)
{
    for (int i = 0; i < tabObjektov.size(); i++)
    {
        if (tabObjektov[i]->imeObjekta == ime)
            return tabObjektov[i];
    }
    return nullptr;
}
void Scena::uniciObjekt(Objekt *kateriObjekt)
{
    delete kateriObjekt;
}
Scena::~Scena()
{
    for (int i = 0; i < tabObjektov.size(); i++)
        delete tabObjektov[i];
}