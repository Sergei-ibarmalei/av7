#include "sdltypes.h"

Cca::~Cca()
{
    arr = nullptr;
}

void Cca::Set(rect_* a, const int len)
{
    if (len <= 0)
    {
        init = false; return;
    }
    arr = a;
    length = len;
}

Cca& Cca::operator=(const Cca& ca)
{
    if (this == &ca) return *this;
    delete[] arr;
    length = ca.length;
    arr = ca.arr;
    return *this;
}

bool Cca::operator==(const Cca& ca)
{
    return (length<=ca.length)? comparis(arr, length, ca.arr):
                                comparis(ca.arr, ca.length, arr);
}

bool Cca::comparis(rect_* f, const int len, rect_* s)
{
    for (int rect = 0; rect < len; ++rect)
    {
        if (f[rect] == s[rect]) return true;
    }
    return false;
}
