#include "n_ob.h"

ObjectList::ObjectList(const tc* collection)
{
    if (!collection)
    {
        init = false; return;
    }
    tcolleciton = collection;
}