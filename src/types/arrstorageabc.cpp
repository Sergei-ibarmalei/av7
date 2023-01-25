#include "n_ob.h"


ArrStorageABC::ArrStorageABC(const int capacity)
{
    if (capacity <= 0)
    {
        init = false; return;
    }
    storageCapacity = capacity;
    counter = 0;
    storage = new (std::nothrow) ElementaryObject*[capacity] {nullptr};
    if (!storage) init = false;
}


/*Полная очистка storage*/
void ArrStorageABC::Clear()
{
    if (counter >= storageCapacity) counter = storageCapacity-1;
    if (counter < 0) counter = 0;
    for (int i = 0; i < counter; ++i)
    {
        delete storage[i];
        storage[i] = nullptr;
    }
    counter = 0;
}

/*Смещение всех значений storage после удаления элем. под номером indexClean*/
bool ArrStorageABC::cleaning(const int indexClean)
{
    if (indexClean < 0 || indexClean >= storageCapacity) return false;
    if (indexClean == (storageCapacity - 1)) return true;

    for (int i = indexClean; i < (storageCapacity-1); ++i)
    {
        storage[i] = storage[i+1];
        storage[i+1] = nullptr;
    }
    counter -= 1;
    return true;
}

void ArrStorageABC::Remove(const int index)
{
    if (index < 0 || index >= storageCapacity) return;
    delete storage[index];
    storage[index] = nullptr;
}



void ArrStorageABC::Sort(const int arrLen)
{
    #define IS_PRESENSE storage[i]
    #define IS_ON_SCREEN storage[i]->OnScreen()
    //#define IS_ALIVE !storage[i]->IsItGone()

    int len = arrLen;
    while (len--)
    {
        bool swaps = false;
        for (int i = 0; i <= len; ++i)
        {
            if (IS_PRESENSE && IS_ON_SCREEN) continue;
            if (storage[i])
            {
                delete storage[i];
                storage[i] = nullptr;
                counter--;
            }
            if (i < arrLen - 1)
            {
                storage[i] = storage[i+1];
                storage[i+1] = nullptr;
                swaps = true;
            }
            swaps = true;
        }
        if (!swaps) break;
    }

    #undef IS_PRESENSE
    #undef IS_ON_SCREEN
    //#undef IS_ALIVE
}

ArrStorageABC::~ArrStorageABC()
{
    for (int i = 0; i < counter; ++i)
    {
        delete storage[i];
        storage[i] = nullptr;
    }
    delete [] storage;
    storage = nullptr;
}

bool ArrStorageABC::Push(ElementaryObject* ob)
{
    if (!ob) return false;
    if (counter >= storageCapacity) return false;
    storage[counter++] = ob;
    return true;
}

