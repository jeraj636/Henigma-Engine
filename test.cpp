#include "Render/render.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Komponente/upodabljalnik.h"
#include "Komponente/transformacija.h"
#include "Ostalo/ostalo.h"
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
    Barva neki(0xff0000ff);
    jj->poisciKomponento<Upodabljalnik>()->barvaObjekta = neki;
    jj->poisciKomponento<Upodabljalnik>()->tekstura = dodajTeksturo("../wall.jpg");
    std::cout.flush();
    Transformacija *tr = jj->poisciKomponento<Transformacija>();
    tr->pozicija.x = 0.5;
    tr->pozicija.y = 0.5;
    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
    }
}