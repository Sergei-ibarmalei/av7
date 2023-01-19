#include "n_ob.h"

#define toLongLazer static_cast<LongLazer*>


/*E_listABC::E_listABC(const tc* collection)
{
    //std::cout << "In E_listABC ctor.\n";
    tcollection = collection;
    first = nullptr;
    last  = nullptr;
    root  = nullptr;
}


E_listABC::~E_listABC()
{
    //std::cout << "In E_listABC dtor.\n";
    while (first)
    {
        obNode* tmp = first;
        first = first->next;
        delete tmp;
    }
}*/

/*obNode* E_listABC::deleteItem(obNode* first, obNode* root)
{
    obNode* temp;
    temp = root;
    while (temp->next != first)
    {
        temp = temp->next;
    }
    temp->next = first->next;
    delete first;
    return temp;
}

bool E_listABC::push(ElementaryObject* ob)
{
    obNode* tmp = new(std::nothrow) obNode;
    if (!tmp) return false;
    tmp->object = ob;
    tmp->next = first;
    first = tmp;
    root = first;
    return true;
}*/



/*void HeroLazersList::Show(const Sdl* sdl)
{
    showLazer(sdl, first);
}



void HeroLazersList::showLazer(const Sdl* sdl, obNode* first)
{
    if (!first) return;
    toLongLazer(first->object)->Show(sdl);
    showLazer(sdl, first->next);
}

bool HeroLazersList::Push(const plot* start)
{
    #define PREVLAZER_X toLongLazer(E_listABC::\
                        GetFirst()->object)->GetLazer_x()
    #define LAZER_W toLongLazer(E_listABC::\
                        GetFirst()->object)->GetLazer_w()

    if (first)
    {
        if (PREVLAZER_X - start->x < LAZER_W * 3) return false;
    }
    if (!(push(new LongLazer(start, dir::right,
                        &E_listABC::tcollection->Pictures()[tn::blue_laser]))))
        return false;

    #undef PREVLAZER_X
    #undef LAZER_W
    return true;
}

void HeroLazersList::Move()
{
    moveNode(first);
}



void HeroLazersList::moveNode(obNode* first)
{
    while (first)
    {
        toLongLazer(first->object)->Move();
        if ( (first->IsAlive == false) || (first->object)->OnScreen() == false)
        {
            if (HeroLazersList::first == HeroLazersList::root)
            {
                std::cout << "by delet lazer first: " << (void*)first << std::endl;
                delete E_listABC::first;
                E_listABC::root = E_listABC::first = nullptr;
                return;
            }
            first = deleteItem(first, root);
            continue;
        }
        first = first->next;
    }
}*/

#undef toLongLazer
