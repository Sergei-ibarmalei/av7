#include "arrstorageabc.h"

ArrStorageABC::ArrStorageABC(const int capacity)
{
    if (capacity <= 0)
    {
        init = false; return;
    }
    storageCapacity = capacity;
    counter = 0;
    live_size = 0;
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



void ArrStorageABC::Remove(const int index)
{
    if (index < 0 || index >= storageCapacity) return;
    delete storage[index];
    storage[index] = nullptr;
    live_size--;
}

bool ArrStorageABC::Clear_at(const int index)
{
    if (index < 0 || index >= storageCapacity) return false;
    storage[index] = nullptr;
    --live_size;
    return true;
}

void ArrStorageABC::Sort(const int arrLen)
{
    #define IS_PRESENSE storage[i]
    #define IS_ON_SCREEN storage[i]->OnScreen()

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
    live_size++;
    return true;
}

ElementaryObject* ArrStorageABC::operator[](const int index)
{
    if (index < 0 || index >= counter) return nullptr;
    return storage[index];
}

