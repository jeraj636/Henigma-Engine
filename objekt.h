#pragma once
#include "objekt.h"
#include <vector>
#include "ostalo.h"
#include "komponenta.h"
class Objekt
{
public:
    uint VAO, shaderProgram;
    Objekt(std::string ime);
    void nastavi();
    void zanka(uint _VAO, uint _shaderProgram);
    std::string dobiIme();
    template <class tipKomponente>
    void dodajKomponento()
    {
        tabKomponent.push_back(new tipKomponente);
        tabKomponent.back()->nastavi();
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
        io::izpis("NI KOMPONENTE", io::type::msg);
        return nullptr;
    }

private:
    std::vector<Komponenta *> tabKomponent;
    std::string _ime;
    Neki nn;
};
