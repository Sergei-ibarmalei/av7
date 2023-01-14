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
    arr = nullptr;
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



bool CRC::comparison(rect_* f, const int len, rect_* s)
{
    for (int rect = 0; rect < len; ++rect)
    {
        if (f[rect] ==s[rect]) return true;
    }
    return false;
}

bool CRC::operator==(const CRC& crc)
{
    return (arrLen < crc.arrLen)? comparison(array, arrLen, crc.array):
                                  comparison(crc.array, crc.arrLen, array);
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
