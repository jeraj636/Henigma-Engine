#pragma once
#include "../Ostalo/ostalo.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "komponenta.h"
#include "../Objekt/objekt.h"
#include "../Render/render.h"
#include <vector>
#include <string>
class Pisava : public Komponenta
{

public:
    void nastavi(Objekt *kazObj, Okno *kazOkno) override;
    void zanka() override;
    Pisava();

private:
};
