#include "n_ob.h"

AliensLazersStorage::AliensLazersStorage(const int capacity):
                                                ArrStorageABC(capacity)
{
    if (!init) return;
}

ElementaryObject* AliensLazersStorage::operator[](const int index)
{
    if (index < 0 || index >= counter) return nullptr;
    return storage[index];
}