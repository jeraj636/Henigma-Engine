#ifndef OBJEKT_H
#define OBJEKT_H
#include <vector>
#include "ostalo.h"
#include "komponenta.h"
class Objekt
{
public:
    uint VAO, shaderProgram;
    Objekt(std::string ime);
    void nastavi();
    void zanka(uint shaderProgram, uint VAO);
    std::string dobiIme();
    void poz();
    template <class T>
    void dodajKomponento()
    {
        tabKomponent.push_back(new T);
        tabKomponent.back()->nastavi();
    }
    template <class T>
    T *poisciKomponento()
    {
        for (int i = 0; i < tabKomponent.size(); i++)
        {
            T *kaz = dynamic_cast<T *>(tabKomponent[i]);
            if (kaz != nullptr)
                return kaz;
        }
        io::izpis("NI TE KOMPONENTE V TEM OBJEKTU", io::type::msg);
        return nullptr;
    }

private:
    std::vector<Komponenta *> tabKomponent;
    std::string _ime;
};
#endif