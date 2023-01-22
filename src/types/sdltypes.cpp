#include "sdltypes.h"



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
}




CRC::CRC(const CRC& crc)
{
    if (crc.arrLen <= 0)
    {
        init = false; 
        return;
    }
    array = new (std::nothrow) rect_[crc.arrLen];
    if (!array)
    {
        init = false; return;
    }
    arrLen = crc.arrLen;
    for (int i = 0; i < arrLen; ++i)
    {
        array[i] = crc.array[i];
    } 

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

bool CRC::operator==(rect_* r)
{
    //return comparison(r, 1, array);
    return comparison(r, arrLen, array);
}

bool CRC::operator==(const rect_ r)
{
    return comparison(&r, 1, array);
}

CRC& CRC::operator=(const CRC& crc)
{
    if (this == &crc) return *this;
    delete array;
    array = new (std::nothrow) rect_[crc.arrLen];
    arrLen = crc.arrLen;
    for (int i = 0; i < arrLen; ++i)
    {
        array[i] = crc.array[i];
    }
    return *this;
}
