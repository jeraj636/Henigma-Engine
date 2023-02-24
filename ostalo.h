#ifndef OSTALO_H
#define OSTALO_H
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
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
#endif