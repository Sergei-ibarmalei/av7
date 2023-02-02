#ifndef ANIMATEDPACK_H
#define ANIMATEDPACK_H

#include "texturescollection.h"
#include "sdlclass.h"


/*Class Animated pack of textures*/


class Apack
{
    protected:
    bool init {true};
    int packCapacity;
    int frame;
    texture_* tpack;

    void setCoords(plot* center);

    public:
    Apack() {}
    Apack(texture_* animPack, const int animPackCap, plot* center);
    Apack(const Apack&) = delete;
    Apack& operator=(const Apack&) = delete;
     ~Apack();
    void Show(const Sdl* sdl, const tn::flow f);
    bool IsItGone() const {return frame == (packCapacity-1);}
    bool Status() const {return init;}
};


/*class ApackList
{
    private:
    struct Node
    {
        Apack* data;
        struct Node* next;
        ~Node()
        {
            delete data;
            data = nullptr;
        }
    };
    struct Node* first;
    struct Node** current;
    public:

    ApackList();
    ~ApackList();
    ApackList(const ApackList&) = delete;
    ApackList& operator=(const ApackList&) = delete;
    void Push(Apack* data);
    void Show(const Sdl* sdl, const tn::flow f);
    void Check_and_clear();

};*/




#endif