#include "cara.h"

Cara &Cara::operator=(const Cara &cara)
{
    a = cara.a;
    b = cara.b;
    c = cara.c;

    return *this;
}
