#include "render.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    Scena glavna;
    Barva br(0xff0000ff);
    glavna.nastavi(800, 600, "heheh");
    glavna.dodajObljekt("jj");
    glavna.poisciObjekt("jj")->dodajKomponento<Upodabljalnik>();
    glavna.poisciObjekt("jj")->poisciKomponento<Upodabljalnik>()->poz();

    glavna.spremeniBarvo(br);
    std::cout.flush();
    while (!glfwWindowShouldClose(glavna.okno))
    {
        glavna.zanka();
    }
}