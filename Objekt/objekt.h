#pragma once
#include "objekt.h"
#include <vector>
#include "../Ostalo/ostalo.h"
#include "../Komponente/komponenta.h"
class Komponenta;
class Okno;
class Objekt
{
public:
    Objekt(std::string ime);
    void nastavi(Okno *kaz);
    void zanka();
    template <class tipKomponente>
    void dodajKomponento()
    {
        tabKomponent.push_back(new tipKomponente);
        nstk();
    }
    template <class tipKomponente>
    tipKomponente *poisciKomponento()
    {
        for (int i = 0; i < tabKomponent.size(); i++)
        {
            tipKomponente *kaz = dynamic_cast<tipKomponente *>(tabKomponent[i]);
            if (kaz != nullptr)
                return kaz;
        }
        return nullptr;
    }
    bool aktivno = 1;
    std::vector<Komponenta *> tabKomponent;
    ~Objekt();
    std::string imeObjekta;

private:
    Okno *_okno;
    void nstk();
};
