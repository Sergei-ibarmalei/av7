#include "sdltypes.h"

std::ostream& operator<<(std::ostream& os, const Rect& r)
{
    os << "[x: " << r.x << ", y: " << r.y << ", w: " << r.w << ", h: " << r.h << "]\n";
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




bool CRC::comparison(const rect_* f, const int len, const rect_* s) const
{
    for (int rect = 0; rect < len; ++rect)
    {
        if (f[rect] == s[rect]) return true;
    }
    return false;
}

bool CRC::operator==(const CRC& crc)
{
    return (arrLen < crc.arrLen)? comparison(array, arrLen, crc.array):
                                  comparison(crc.array, crc.arrLen, array);
}

bool CRC::operator==(const CRC* crc)
{
    return (arrLen < crc->arrLen)? comparison(array, arrLen, crc->array):
                                    comparison(crc->array, crc->arrLen, array);
}

bool CRC::operator==(rect_* r)
{
    return cmp_oneTomany(r);
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
