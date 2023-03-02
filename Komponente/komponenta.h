#pragma once
#include "../Objekt/objekt.h"
#include "../Ostalo/ostalo.h"
class Okno;
class Objekt;
class Komponenta
{
public:
    virtual void nastavi(Objekt *kazObj, Okno *kazOkno) = 0;
    virtual void zanka() = 0;
    bool aktivno = 1;
    Objekt *obj;
    Okno *okno;
};
