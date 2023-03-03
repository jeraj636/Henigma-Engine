#include "Render/render.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Komponente/upodabljalnik.h"
#include "Komponente/transformacija.h"
// #define STB_IMAGE_IMPLEMENTATION
int main()
{
    Okno okno;
    Barva br(0xff0000ff);
    okno.nastavi(800, 600, "heheh");

    okno.dodajSceno("glavna");
    Scena *glavna = okno.poisciSceno("glavna");
    Objekt *jj = glavna->dodajObjekt("jj");
    jj->dodajKomponento<Transformacija>();
    jj->dodajKomponento<Upodabljalnik>();
    Barva neki(0xffffffff);
    jj->poisciKomponento<Upodabljalnik>()->barvaObjekta = neki;
    std::cout.flush();
    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
    }
}