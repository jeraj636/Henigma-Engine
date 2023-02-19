#include "render.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    int visina = 1080, dolzina = 1920;

    Okno okno(600, 900);
    Barva b(0x000000ff);
    GameObject mapaOdzadje(visina, dolzina);

    mapaOdzadje.spremeniMiBarvo(Barva(0x0000ffff));

    bool aliNajZaprem = 0;
    mapaOdzadje.velikost.y = 50;
    mapaOdzadje.velikost.x = 50;
    double xCpos, yCpos;
    while (!okno.aliMoramZapreti())
    {
        glfwGetWindowSize(okno.okno, &visina, &dolzina);
        okno.pobarvaj(b);
        mapaOdzadje.narisiMe(visina, dolzina);

        glfwGetCursorPos(okno.okno, &xCpos, &yCpos);
        // yCpos = (int)yCpos * 2 * visina / 1042 - visina;
        // xCpos = (int)xCpos * 2 * dolzina / 1919 - dolzina;
        std::cout << xCpos << "       " << yCpos << '\n';
        // mapaOdzadje.pozicija.x = xCpos;

        okno.BeriInput();
        okno.osvezi();
    }
}