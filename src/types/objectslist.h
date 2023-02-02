#ifndef OBJECTSLIST_H
#define OBJECTSLIST_H

#include "nhero.h"
#include "texturesnames.h"


template<class T>
class ObjectsList
{
    private:
    template<class N>
    struct Node
    {
        N* data;
        struct Node* next;
        ~Node()
        {
            delete data;
            data = nullptr;
        }
    };
    struct Node<T>* first;
    struct Node<T>** current;

    public:
    ObjectsList();
    ~ObjectsList();
    ObjectsList(const ObjectsList&) = delete;
    ObjectsList& operator=(const ObjectsList&) = delete;
    void Push(T* data);
    void Show(const Sdl* sdl) const;
    void Show(const Sdl* sdl, tn::flow f);
    void Check_and_clear();
    bool Check_withObject(NHero* hero);
    void Move();
    bool IsEmpty();
    void ClearList();


};

template<class T>
bool ObjectsList<T>::IsEmpty()
{
    return (first == nullptr);
}

template<class T>
ObjectsList<T>::ObjectsList()
{
    first = nullptr;
}

template<class T>
void ObjectsList<T>::ClearList()
{
    while (first)
    {
        struct Node<T>* tmp = first;
        first = first->next;
        delete tmp;
        tmp = nullptr;
    }
}

template<class T>
ObjectsList<T>::~ObjectsList()
{
    while (first)
    {
        struct Node<T>* tmp = first;
        first = first->next;
        delete tmp;
        tmp = nullptr;
    }
}

template<class T>
void ObjectsList<T>::Push(T* data)
{
    if (!data) return;
    struct Node<T>* tmp = new (std::nothrow) Node<T>;
    if (!tmp) return;
    tmp->data = data;
    if (!first)
    {
        tmp->next = nullptr;
        first = tmp;
        return; 
    }
    tmp->next = first;
    first = tmp;
    return;
}

template<class T>
void ObjectsList<T>::Show(const Sdl* sdl) const
{
    if (!first) 
    {
        return;
    }
    struct Node<T>* tmp = first;
    while (tmp)
    {
        tmp->data->Show(sdl);
        tmp = tmp->next;
    }

}

template<class T>
void ObjectsList<T>::Show(const Sdl* sdl, tn::flow f)
{
    if (!first) 
    {
        return;
    }
    struct Node<T>* tmp = first;
    while (tmp)
    {
        tmp->data->Show(sdl, f);
        tmp = tmp->next;
    }
}

template<class T>
void ObjectsList<T>::Check_and_clear()
{
    current = &first;
    while (*current)
    {
        if ( (*current)->data->IsItGone())
        { 
            struct Node<T>* tmp = *current;
            *current = (*current)->next;
            delete tmp;
        }
        else current = &(*current)->next;
    }
}


/*Проверка на столкновение с героем*/
template<class T>
bool ObjectsList<T>::Check_withObject(NHero* hero)
{
    if (!first) return false;

    /*Если герой уже подбит, выходим*/
    if (hero->IsItGone() == true) return false;

    current = &first;
    while(*current)
    {
        if ( *((*current)->data) == *hero)
        {
            struct Node<T>* tmp = *current;
            *current = (*current)->next;
            delete tmp;
            //отмечаем,что героя подбили
            hero->ItIsGoneNow();
            return true;
        }
        else current = &(*current)->next;
    }
    return false;
}

template<class T>
void ObjectsList<T>::Move()
{
    if (!first) return;
    struct Node<T>* tmp = first;
    while(tmp)
    {
        tmp->data->Move();
        tmp = tmp->next;
    }
}
#endif