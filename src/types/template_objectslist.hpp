#ifndef TEMPLATE_OBJECTSLIST_HPP
#define TEMPLATE_OBJECTSLIST_HPP

#include "sdlclass.h"

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
    void Check();
    void Move();


};

template<class T>
ObjectsList<T>::ObjectsList()
{
    first = nullptr;
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
void ObjectsList<T>::Check()
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