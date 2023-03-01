#pragma once
#include "../Objekt/objekt.h"
#include "../Ostalo/ostalo.h"

class Objekt;
class Komponenta
{
public:
    virtual void nastavi(Objekt *kaz) = 0;
    virtual void zanka() = 0;
    bool aktivno = 1;
    Objekt *obj;
};
