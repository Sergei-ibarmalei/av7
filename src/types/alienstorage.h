#ifndef ALIENSTORAGE_H
#define ALIENSTORAGE_H

#include "arrstorageabc.h"
#include "alien.h"

class AlienStorage: public ArrStorageABC
{
    public:
    explicit AlienStorage(const int capacity);
    ~AlienStorage() {}
    AlienStorage(const AlienStorage&) = delete;
    AlienStorage& operator=(const AlienStorage&) = delete;
    Alien* operator[](const int index);
};



#endif