#pragma once
#include "objekt.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ostalo.h"
class Objekt;
class Komponenta
{
public:
    virtual void nastavi() = 0;
    virtual void zanka(Objekt *obj) = 0;
    bool aktivno = 1;
};
