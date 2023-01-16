#include "n_ob.h"

E_listABC::E_listABC(const tc* collection)
{
    std::cout << "In E_listABC ctor.\n";
    tcollection = collection;
    first = nullptr;
    root  = nullptr;
}


E_listABC::~E_listABC()
{
    std::cout << "In E_listABC dtor.\n";
    while (first)
    {
        obNode* tmp = first;
        first = first->next;
        delete tmp;
    }
}

void E_listABC::push(ElementaryObject* ob)
{
    obNode* tmp = new obNode;
    tmp->object = ob;
    tmp->next = first;
    first = tmp;
    root = first;

}

void HeroLazersList::Show(const Sdl* sdl)
{
    showLazer(sdl, first);
}

void HeroLazersList::showLazer(const Sdl* sdl, obNode* first)
{
    if (!first) return;
    static_cast<const LongLazer*>(first->object)->Show(sdl);
    #ifdef SHOW_COL_R
        static_cast<const LongLazer*>(first->object)->ShowColR(sdl);
    #endif
    showLazer(sdl, first->next);
}

void HeroLazersList::Push(const plot* start)
{
    #define PREVLAZER_X static_cast<LongLazer*>(E_listABC::\
                        GetFirst()->object)->GetLazer_x()
    #define LAZER_W static_cast<LongLazer*>(E_listABC::\
                        GetFirst()->object)->GetLazer_w()

    if (first)
    {
        if (PREVLAZER_X - start->x < LAZER_W * 3) return;
    }
    E_listABC::push(new LongLazer(start, dir::right, 
                    &E_listABC::tcollection->Pictures()[tn::blue_laser]));

    #undef PREVLAZER_X
    #undef LAZER_W
}

void HeroLazersList::Move()
{
    moveLazer(first);
}

obNode* deletelem(obNode* first, obNode* root)
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

void HeroLazersList::moveLazer(obNode* first)
{
    while (first)
    {
        static_cast<LongLazer*>(first->object)->Move();
        if (static_cast<LongLazer*>(first->object)->OnScreen() == false)
        {
            if (first == root)
            {
                delete E_listABC::first;
                E_listABC::root = E_listABC::first = nullptr;
                return;
            }
            first = deletelem(first, root);
            continue;
        }
        first = first->next;
    }
}
