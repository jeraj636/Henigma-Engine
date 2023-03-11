#ifndef OSTALO_H
#define OSTALO_H
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "../Render/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Barva
{
public:
    float r, g, b, a;
    Barva(int hexCode);
};
namespace io
{
    enum class type
    {
        msg,
        warning,
        error
    };
    void izpis(const char *msg, const type &tip);

    template <typename t>
    void vpis(const char *msg, t &input);

}
class Vec3
{
public:
    float x, y, z;
    Vec3()
    {
        x = 1;
        y = 1;
        z = 1;
    }
};
class Znak
{
public:
    uint ID;

private:
};
static uint dodajTeksturo(const char *imeDatoteke)
{
    //*tukaj je bil Jakob
    //! program mu ni delal in bil je jezen
    //?jezil se je na prevajalnik in na cmake
    // udarjal je po mizi
    //*ves ta cas je bil glavni krivec napake git

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    uint tekstura;
    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int dolzina, visina, kanali;
    stbi_set_flip_vertically_on_load(1);
    u_char *data = stbi_load(imeDatoteke, &dolzina, &visina, &kanali, STBI_rgb_alpha);
    if (data != NULL)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dolzina, visina, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    return tekstura;
}

#endif