#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
// #include "render.h"
#include "ostalo.h"
#include "komponenta.h"
class Objekt
{
public:
    Okno *okno;
    uint shaderProgram, VAO;
    Objekt(std::string ime)
    {
        _ime = ime;
    }
    void nastavi()
    {
    }
    void zanka()
    {
        for (int i = 0; i < tabKomponent.size(); i++)
        {
            if (tabKomponent[i]->aktivno)
                tabKomponent[i]->zanka(this);
        }
    }

    std::string dobiIme()
    {
        return _ime;
    }
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
        // io::izpis("NI TE KOMPONENTE V TEM OBJEKTU", io::type::msg);
        return nullptr;
    }

private:
    std::vector<Komponenta *> tabKomponent;
    std::string _ime;
};