#ifndef ARRSTORAGEABC_H
#define ARRSTORAGEABC_H
#include "elementaryobject.h"


class ArrStorageABC
{
    protected:
    bool init {true};
    int storageCapacity;
    int counter;
    //Подсчет живых
    int live_size;

    ElementaryObject** storage;

    public:
    ArrStorageABC(const int capacity);
    ArrStorageABC(const ArrStorageABC&) = delete;
    ArrStorageABC& operator=(const ArrStorageABC&) = delete;

    ElementaryObject* operator[](const int index);

    virtual ~ArrStorageABC() = 0;
    bool Status() const {return init;}
    void Clear();
    void Push(ElementaryObject* ob);
    bool Clear_at(const int index);

    int  GetCounter()   {return counter;}
    void Remove(const int index);
    void Sort(const int arrLen);
    bool IsEmpty() const {return live_size == 0;}
    int  GetLiveSize() const {return live_size;}
    

};


#endif