#ifndef OSTALO_H
#define OSTALO_H
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "../Render/stb_image.h"

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

static uint dodajTeksturo(const char *imeDatoteke)
{
    uint tekstura;
    glGenTextures(1, &tekstura);
    glBindTexture(GL_TEXTURE_2D, tekstura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int dolzina, visina, kanali;
    u_char *data = stbi_load(imeDatoteke, &dolzina, &visina, &kanali, 0);
    if (data != NULL)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dolzina, visina, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    return tekstura;
}

#endif