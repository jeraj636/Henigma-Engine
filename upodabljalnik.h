#pragma once
#include "ostalo.h"
#include "komponenta.h"
#include "objekt.h"
class Upodabljalnik : public Komponenta
{

public:
        void nastavi() override;
        void zanka(Objekt *obj) override;
};
