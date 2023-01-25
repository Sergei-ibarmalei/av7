#include "loging.h"

/*namespace log_
{
    Log::Log()
    {
        first = current = nullptr;
    }

    Log::~Log()
    {
        if (!first) return;
        deleting(first);
    }

    void Log::deleting(Node* first)
    {
        if (!first) return;
        Node* tmp = first;
        delete first->info;
        first->info = nullptr;
        first = first->next;
        delete tmp;
        tmp = nullptr;
        deleting(first);
    }

    void Log::push(const string_& log_info)
    {
        Node* tmp = new Node;
        if (!current)
        {
            current = tmp;
            current->next = nullptr;
            current->info = new string_;
            *current->info = log_info;
            first = current;
            return;
        }
        tmp->info = new string_;
        *tmp->info = log_info;
        tmp->next = nullptr;
        current->next = tmp;
        current = tmp;
    }

    void Log::Show()
    {
        showInfo(first);
    }

    void Log::showInfo(Node* first)
    {
        if (!first) return;
        std::cout  << *first->info << std::endl;
        showInfo(first->next);
    }
}*/


