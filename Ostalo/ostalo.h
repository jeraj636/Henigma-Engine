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
#include <vector>
#include <string>
#include <freetype2/freetype/config/ftheader.h>
#include <freetype2/ft2build.h>
/*
naredil sem da naloi posamezne glife v classu Pisava kot tip Znak
obtical sem na 7 strani sklopa mojih skript to sem napisal dne 11. 3. 2023
*/
#include FT_FREETYPE_H
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
    uint IDTekstura;
    glm::vec2 velikos;
    glm::vec2 zamik;
    uint zamikNaslednjega;
};
class Pisava
{

public:
    std::vector<Znak *> tabZnakov;
    Pisava(const char *potDoPisave, int velikost)
    {
        if (FT_Init_FreeType(&_ft))
            io::izpis("ni ok", io::type::error);
        if (FT_New_Face(_ft, potDoPisave, 0, &_face))
            io::izpis("ni obraza", io::type::error);
        FT_Set_Pixel_Sizes(_face, 0, velikost);
        for (u_char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
                continue;
            uint tekstura;
            glGenTextures(1, &tekstura);
            glBindTexture(GL_TEXTURE_2D, tekstura);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _face->glyph->bitmap.width, _face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, _face->glyph->bitmap.buffer);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            tabZnakov.push_back(new Znak);
            tabZnakov.back()->IDTekstura = tekstura;
            tabZnakov.back()->velikos = glm::vec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows);
            tabZnakov.back()->zamik = glm::vec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top);
            tabZnakov.back()->zamikNaslednjega = _face->glyph->advance.x;
        }
    }

private:
    FT_Library _ft;
    FT_Face _face;
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