#include "render.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    Okno okno;
    Barva br(0xff0000ff);
    okno.nastavi(800, 600, "heheh");
    okno.dodajObljekt("jj");
    // okno.poisciObjekt("jj")->dodajKomponento<Upodabljalnik>();
    okno.poisciObjekt("jj")->dodajKomponento<Upodabljalnik>();
    okno.spremeniBarvo(br);
    std::cout.flush();
    while (!glfwWindowShouldClose(okno.okno))
    {
        okno.zanka();
    }
}