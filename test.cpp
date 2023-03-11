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
    Pisava pis("../font.ttf", 69);
    okno.dodajSceno("glavna");
    Scena *glavna = okno.poisciSceno("glavna");
    Objekt *jj = glavna->dodajObjekt("jj");
    jj->dodajKomponento<Transformacija>();
    jj->dodajKomponento<Upodabljalnik>();
    Barva neki(0xffffffff);
    jj->poisciKomponento<Upodabljalnik>()->barvaObjekta = neki;
    jj->poisciKomponento<Upodabljalnik>()->tekstura = dodajTeksturo("../tt.png");
    std::cout.flush();
    Transformacija *tr = jj->poisciKomponento<Transformacija>();
    tr->pozicija.x = 0;
    tr->pozicija.y = 0;
    tr->velikost.x = 0.5;
    tr->velikost.y = 0.5;
    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
    }
}