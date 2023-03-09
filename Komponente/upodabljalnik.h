#pragma once
#include "../Ostalo/ostalo.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "komponenta.h"
#include "../Objekt/objekt.h"
#include "../Render/render.h"
class Upodabljalnik : public Komponenta
{

public:
        void nastavi(Objekt *kazObj, Okno *kazOkno) override;
        void zanka() override;
        Barva barvaObjekta;
        Upodabljalnik();
        uint tekstura;

private:
        int _lokacijaBarve;
        int _lokacijaTeksture;
};
