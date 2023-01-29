#include "sdltypes.h"

std::ostream& operator<<(std::ostream& os, const Rect& r)
{
    os << "[x: " << r.x << ", y: " << r.y <<
                             ", w: " << r.w << ", h: " << r.h << "]\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const plot_& p)
{
    os << "[x: " << p.x << ", y: " << p.y << "]\n";
    return os;
}

CRC::CRC(const int len)
{
    if (len <= 0)
    {
        init = false; return;
    }
    array = new (std::nothrow) rect_[len];
    if (!array)
    {
        init = false; return;
    }
    arrLen = len;
}




bool CRC::comparison(const rect_* f, const int shortlen, const rect_* s, 
                                                    const int longlen) const
{
    for (int shortrect = 0; shortrect < shortlen; ++shortrect)
    {
        for (int longrect = 0; longrect < longlen; ++longrect)
        {
            if (f[shortrect] == s[longrect]) return true;
        }
    }
    return false;
}


bool CRC::operator==(CRC* crc)
{
    return (arrLen < crc->arrLen)? comparison(array, arrLen, crc->array, 
                                                                crc->arrLen):
                                    comparison(crc->array, crc->arrLen, array, 
                                                                arrLen);
}

bool CRC::operator==(const rect_* r)
{
    return cmp_oneTomany(r);
}

bool CRC::operator==(const rect_& r)
{
    return cmp_oneTomany(&r);
}



bool CRC::cmp_oneTomany(const rect_* one)
{
    for (int rect = 0; rect < arrLen; ++rect)
    {
        if (*one == array[rect])
        {
            return true;
        }
    }
    return false;
}
