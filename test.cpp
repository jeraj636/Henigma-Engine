#include "Render/render.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Komponente/upodabljalnik.h"
int main()
{
    Okno okno;
    Barva br(0xff0000ff);
    okno.nastavi(800, 600, "heheh");

    okno.dodajSceno("glavna");
    Scena *glavna = okno.poisciSceno("glavna");
    Objekt *jj = glavna->dodajObjekt("jj");
    jj->dodajKomponento<Upodabljalnik>();
    std::cout.flush();
    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
    }
}