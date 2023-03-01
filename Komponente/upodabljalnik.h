#pragma once
#include "../Ostalo/ostalo.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "komponenta.h"
#include "../Objekt/objekt.h"
class Upodabljalnik : public Komponenta
{

public:
        void nastavi(Objekt *obj) override;
        void zanka() override;
};
