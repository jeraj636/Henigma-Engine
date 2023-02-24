#ifndef KOMPONENTA_H
#define KOMPONENTA_H
#include "objekt.h"

class Komponenta
{
public:
    virtual void nastavi() = 0;
    virtual void zanka() = 0;
    bool aktivno = 1;
    Objekt neki;
};
class Upodabljalnik : public Komponenta
{
public:
    void nastavi() override
    {
        io::izpis("nastavljeno", io::type::msg);
    }
    void zanka() override
    {

        io::izpis("nastavljeno", io::type::msg);
    }
    Upodabljalnik()
    {
        io::izpis("nastavljeno", io::type::msg);
    }
};
#endif