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
    uint VAO, shaderProgram;
    Objekt(std::string ime);
    void nastavi(Okno *kaz);
    void zanka();
    std::string dobiIme();
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

    std::vector<Komponenta *> tabKomponent;
    ~Objekt();

private:
    std::string _ime;
    Okno *_okno;
    void nstk();
};
