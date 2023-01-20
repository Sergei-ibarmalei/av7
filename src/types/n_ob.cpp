#include "n_ob.h"
#include "../core/checkcrossing.h"



ElementaryObject::~ElementaryObject()
{
    //std::cout << "In ElementaryObject dtor.\n";

    obj_texture->texture = nullptr;
    delete obj_texture;
    obj_texture = nullptr;
    delete obj_velocities;
    obj_velocities = nullptr;
}


ElementaryObject::ElementaryObject(const texture_* t)
{
    //std::cout << "In ElementaryObject ctor.\n";
    if (!t)
    {
        init = false;
        return;
    }
    obj_texture = new (std::nothrow) texture_;
    obj_texture->texture = t->texture;
    obj_texture->main_rect.w = t->main_rect.w;
    obj_texture->main_rect.h = t->main_rect.h;
    obj_texture->main_rect.x = obj_texture->main_rect.y = 0;
    obj_velocities = new plot{0, 0};

}

ElementaryObject::ElementaryObject(const ElementaryObject& eo)
{
    obj_texture = new (std::nothrow) texture_;
    obj_texture->texture = eo.obj_texture->texture;
    obj_texture->main_rect = eo.obj_texture->main_rect;
    obj_velocities = new (std::nothrow) plot;
    obj_velocities->x = eo.obj_velocities->x;
    obj_velocities->y = eo.obj_velocities->y;
}

ElementaryObject& ElementaryObject::operator=(const ElementaryObject& eo)
{
    if (this == &eo) return *this;
    obj_texture->texture = nullptr;
    delete obj_texture;
    obj_texture = new (std::nothrow) texture_;
    obj_texture->texture = eo.obj_texture->texture;
    obj_texture->main_rect = eo.obj_texture->main_rect;
    return *this;
}

bool ElementaryObject::operator==(const ElementaryObject& eo)
{
    return obj_texture->main_rect == eo.obj_texture->main_rect;
}

bool ElementaryObject::operator==(const ElementaryObject* peo)
{
    return obj_texture->main_rect == peo->obj_texture->main_rect;
}

void ElementaryObject::ShowObj(const Sdl* sdl) const
{
    sdl->TextureRender(obj_texture->texture, &obj_texture->main_rect);
    #ifdef SHOW_COL_R
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF, 0, 0, 0xFF);
        SDL_RenderDrawRect(sdl->Renderer(), &obj_texture->main_rect);
        SDL_SetRenderDrawColor(sdl->Renderer(), 0, 0, 0, 0);
    #endif
}


void ElementaryObject::resetUpLeftCorner()
{
    obj_texture->main_rect.x += obj_velocities->x;
    obj_texture->main_rect.y += obj_velocities->y;
}

void ElementaryObject::setUpLeftCorner(const int x, const int y)
{
    obj_texture->main_rect.x = x;
    obj_texture->main_rect.y = y;
}

void ElementaryObject::resetUpLeftCorner_x(const int x)
{
    obj_texture->main_rect.x += x;
}

void ElementaryObject::resetUpLeftCorner_y(const int y)
{
    obj_texture->main_rect.y += y;
}


ComplexObject::ComplexObject(const ComplexObject& co): ElementaryObject(co)
{
    delete cr;
    cr = new (std::nothrow) CRC(co.collisionArrLen);
    *cr = *co.cr;
}

ComplexObject::~ComplexObject()
{
    //std::cout << "In ComplexObject dtor.\n";
    delete cr;
    cr = nullptr;

    //В этом конструкторе не удаляем lazerStart, поскольку
    //lazerStart может быть массивом для нескольких точек
    //Удаляем в конкретном классе
    
}



/// @brief Абстрактный класс
/// @param t текстура
/// @param arrLen длинна массива прям. пересечений
ComplexObject::ComplexObject(const texture_* t, const int arrLen): 
                                                    ElementaryObject(t)
{
    //std::cout << "In ComplexObject ctor.\n";
    if (arrLen <= 0)
    {
        ElementaryObject::init = false; return;
    }
    collisionArrLen = arrLen;
    cr = new (std::nothrow) CRC(collisionArrLen);
    if (cr->Status() == false)
    {
        ElementaryObject::init = false; return;
    }
}

bool ComplexObject::operator==(const ElementaryObject& eo)
{
    //return ElementaryObject::obj_texture->main_rect == eo.MainRect();
    if (ElementaryObject::obj_texture->main_rect ==eo.MainRect())
    {
        return *cr == &eo.MainRect();
    }
    return false;
}

bool ComplexObject::operator==(const ElementaryObject* eo)
{
    if (ElementaryObject::obj_texture->main_rect == eo->MainRect())
    {
        return *cr == eo->MainRect();
    }
    return false;
}

bool ComplexObject::operator==(const ComplexObject& co)
{
    if (ElementaryObject::obj_texture->main_rect == co.MainRect())
    {
        return *cr == *co.cr;
    }
    return false;
}

void ComplexObject::Show(const Sdl* sdl) const
{
    ElementaryObject::ShowObj(sdl);
    #ifdef SHOW_COL_R
        SDL_SetRenderDrawColor(sdl->Renderer(), 0xFF, 0, 0, 0xFF);
        for (int r = 0; r < collisionArrLen; ++r)
        {
            SDL_RenderDrawRect(sdl->Renderer(), &cr->Array()[r]);
        }
    #endif
}




NHero::NHero(const texture_* t): ComplexObject(t, re::heros::allR)
{
    if (ComplexObject::init == false) return;

    #define HEROSTART_X -BORDER_THICKNESS\
             - ElementaryObject::obj_texture->main_rect.w
    #define HEROSTART_Y S_H / 2\
             - ElementaryObject::obj_texture->main_rect.h / 2

    initHeroStopIntro();
    setToStartPos(HEROSTART_X, HEROSTART_Y);
    setCr();
    initLazerStart();
    
    #undef HEROSTART_X
    #undef HEROSTART_Y
}

void NHero::initHeroStopIntro()
{
    #define HERO_W ElementaryObject::obj_texture->main_rect.w

    heroStopIntro = new plot;
    heroStopIntro->x = BORDER_THICKNESS + (4 * HERO_W);
    heroStopIntro->y = ElementaryObject::obj_texture->main_rect.y;

    #undef HERO_W
}


void NHero::setToStartPos(const int startx, const int starty)
{
    ElementaryObject::setUpLeftCorner(startx, starty);
}


/*Определение прям. пересечений*/
void NHero::setCr()
{
    #define CR ComplexObject::cr->Array()
    #define ONE re::heros::one
    #define TWO re::heros::two
    #define THREE re::heros::three
    #define FOUR re::heros::four
    #define FIVE re::heros::five

    #define MAINR_UPLEFT_X ElementaryObject::GetMainRect_x()
    #define MAINR_UPLEFT_Y ElementaryObject::GetMainRect_y()

    CR[ONE].x = MAINR_UPLEFT_X + 2;
    CR[ONE].y = MAINR_UPLEFT_Y + 4;
    CR[ONE].w = 45;
    CR[ONE].h = 17;


    CR[TWO].x = MAINR_UPLEFT_X + 19;
    CR[TWO].y = CR[ONE].y + CR[ONE].h;
    CR[TWO].h = 16;
    CR[TWO].w = 68;

    CR[THREE].x = CR[TWO].x;
    CR[THREE].y = CR[TWO].y + CR[TWO].h;
    CR[THREE].w = 117;
    CR[THREE].h = 36;

    CR[FOUR].x = CR[TWO].x;
    CR[FOUR].y = CR[THREE].y + CR[THREE].h;
    CR[FOUR].w = CR[TWO].w;
    CR[FOUR].h = 16;

    CR[FIVE].x = CR[ONE].x;
    CR[FIVE].y = CR[FOUR].y + CR[FOUR].h;
    CR[FIVE].w = CR[ONE].w;
    CR[FIVE].h = CR[ONE].h;


    #undef MAINR_UPLEFT_X
    #undef MAINR_UPLEFT_Y
    #undef CR
    #undef FIVE
    #undef FOUR
    #undef THREE
    #undef TWO
    #undef ONE
}

NHero::~NHero()
{
    delete heroStopIntro;
    heroStopIntro = nullptr;
    delete lazerStart;
    lazerStart = nullptr;
}

void NHero::initLazerStart()
{
    ComplexObject::lazerStart = new plot;
    recomputeLazerStart();

}

void NHero::recomputeLazerStart()
{
    #define HERO_W ElementaryObject::GetMainRectW()

    #define HERO_H_HALF ElementaryObject::GetMainRectH_Half()

    lazerStart->x = HERO_W + PLAINLASER_OFFSET;
    lazerStart->y = HERO_H_HALF;

    #undef HERO_H_HALF
    #undef HERO_W
}

void NHero::HeroMovesInIntro(status_t& status)
{
    #define HERO_MR_X ElementaryObject::GetMainRect_x()
    #define HERO_W ElementaryObject::GetMainRectW()

    if ( (HERO_MR_X + HERO_W) >= heroStopIntro->x)
    {
        status.heroIntro = false;
        setCr();
        return;
    }
    ElementaryObject::resetUpLeftCorner_x(HERO_VELOCITY_X);

    #undef HERO_W
    #undef HERO_MR_X
}



void NHero::HeroUp()
{
    ElementaryObject::Velocities()->y -= HERO_VELOCITY_Y;
    NHero::Move();
}

void NHero::HeroDown()
{
    ElementaryObject::Velocities()->y += HERO_VELOCITY_Y;
    NHero::Move();
}

void NHero::HeroRight()
{
    ElementaryObject::Velocities()->x += HERO_VELOCITY_X;
    NHero::Move();
}

void NHero::HeroLeft()
{
    ElementaryObject::Velocities()->x -= HERO_VELOCITY_X;
    NHero::Move();
}

void NHero::HeroStop()
{
    ElementaryObject::Velocities()->x = ElementaryObject::Velocities()->y = 0;
}

void NHero::Move()
{
    if (isGonnaCrossUp())    return;
    if (isGonnaCrossDown())  return;
    if (isGonnaCrossRight()) return;
    if (isGonnaCrossLeft())  return;
    ElementaryObject::resetUpLeftCorner();

    NHero::setCr();

    NHero::recomputeLazerStart();
}




bool NHero::isGonnaCrossUp()
{
    #define MAIN_RECT_UP ElementaryObject::GetMainRect_y()
    #define VELOCITY_Y ElementaryObject::Velocities()->y

    return isGonnaCrossUp_check(MAIN_RECT_UP, VELOCITY_Y);

    #undef MAIN_RECT_UP
    #undef VELOCITY_Y
}


bool NHero::isGonnaCrossDown()
{
    #define MAIN_RECT_HEIGHT ElementaryObject::GetMainRectH()
    #define VELOCITY_Y ElementaryObject::Velocities()->y

    return isGonnaCrossDown_check(MAIN_RECT_HEIGHT, VELOCITY_Y);

    #undef MAIN_RECT_HEIGHT
    #undef VELOCITY_Y

}

bool NHero::isGonnaCrossRight()
{
    #define MAIN_RECT_WIDTH ElementaryObject::GetMainRectW()
    #define VELOCITY_X ElementaryObject::Velocities()->x

    return isGonnaCrossRight_check(MAIN_RECT_WIDTH, VELOCITY_X);

    #undef MAIN_RECT_WIDTH 
    #undef VELOCITY_X 
}

bool NHero::isGonnaCrossLeft()
{
    
    #define MAIN_RECT_LEFT ElementaryObject::GetMainRect_x()
    #define VELOCITY_X ElementaryObject::Velocities()->x

    return isGonnaCrossLeft_check(MAIN_RECT_LEFT, VELOCITY_X);

    #undef MAIN_RECT_LEFT 
    #undef VELOCITY_X 
}


PlainAlienABC::PlainAlienABC(const texture_* t, 
                             const int arrLen, 
                             const plot* start,
                             const texture_* lazer): ComplexObject(t, arrLen)
{
    //std::cout << "In PlainAlienABC ctor.\n";
    lazerMainRect = new rect_;
    lazerMainRect->w = lazer->main_rect.w;
    lazerMainRect->h = lazer->main_rect.h;
    setToStartPos(start->x, start->y);
    initLazerStart();
    ElementaryObject::ResetOnScreen(false);
}

PlainAlienABC::~PlainAlienABC()
{
    //std::cout << "In PlainAlienABC dtor.\n";
    delete lazerMainRect;
    lazerMainRect = nullptr;
    delete lazerStart;
    lazerStart = nullptr;
}

void PlainAlienABC::setToStartPos(const int x, const int y)
{
    ElementaryObject::setUpLeftCorner(x, y);
}

void PlainAlienABC::initLazerStart()
{
    ComplexObject::lazerStart = new plot;
    recomputeLazerStart();
}

void PlainAlienABC::recomputeLazerStart()
{
    #define PLAINALIEN_X ElementaryObject::GetMainRect_x()
    #define PLAINALIEN_H_HALF ElementaryObject::GetMainRectH_Half()

    ComplexObject::lazerStart->x = 
            PLAINALIEN_X - lazerMainRect->w - PLAINALIENLASER_OFFSET;
    ComplexObject::lazerStart->y = PLAINALIEN_H_HALF;

    #undef  PLAINALIEN_X
    #undef  PLAINALIEN_H_HALF
}

void PlainAlienABC::show(const Sdl* sdl) const
{
    ComplexObject::Show(sdl);
}




PlainAlien_t1::PlainAlien_t1(const texture_* t,
                             const plot* start,
                             const texture_* lazer):PlainAlienABC(t,
                             re::alien_t1::t1_allR, start, lazer)
{
    //std::cout << "In PlainAlien_t1 ctor.\n";
    ElementaryObject::Velocities()->x = -ALIENFLEET_ONE_VELOCITY;
    ElementaryObject::Velocities()->y = 0;
}

PlainAlien_t1::~PlainAlien_t1()
{
    //std::cout << "In PlainAlien_t1 dtor.\n";
}

void PlainAlien_t1::Show(const Sdl* sdl)
{
    PlainAlienABC::Show(sdl);
}

void PlainAlien_t1::setCr()
{
    #define CR ComplexObject::cr->Array()
    #define ONE re::alien_t1::t1_one
    #define TWO re::alien_t1::t1_two
    #define THREE re::alien_t1::t1_three
    #define MAINR_UPLEFT_X ElementaryObject::GetMainRect_x()
    #define MAINR_UPLEFT_Y ElementaryObject::GetMainRect_y()


    CR[ONE].x = MAINR_UPLEFT_X + 32;
    CR[ONE].y = MAINR_UPLEFT_Y;
    CR[ONE].w = 39;
    CR[ONE].h = 31;

    CR[TWO].x = MAINR_UPLEFT_X + 4;
    CR[TWO].y = CR[ONE].y + CR[ONE].h;
    CR[TWO].w = 87;
    CR[TWO].h = 32;

    CR[THREE].x = CR[ONE].x;
    CR[THREE].y = CR[TWO].y + CR[TWO].h;
    CR[THREE].w = CR[ONE].w;
    CR[THREE].h = CR[ONE].h;



    #undef CR
    #undef ONE
    #undef TWO
    #undef THREE
}

void PlainAlien_t1::Move()
{
    ElementaryObject::resetUpLeftCorner();
    setCr();
    //Если вышла на экран
    if (hasCrossedRight_fromOut(ElementaryObject::GetMainRect_x()))
    {
        ElementaryObject::ResetOnScreen(true);
    }
    //Если вышли за левую границу экрана, то удаляемся
    if (hasCrossedLeft_fromScreen(ElementaryObject::GetMainRectW()))
    {
        ElementaryObject::ResetOnScreen(false);
        Gone() = true;
    }
}




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

bool ArrStorageABC::Remove(const int index)
{
    if (index < 0 || index >= storageCapacity) return false;
    delete storage[index];
    storage[index] = nullptr;
    return cleaning(index);
}

void ArrStorageABC::Sort(const int arrLen, int& counter)
{
    #define OBJECT_ON_SCREEN storage[i] && storage[i]->OnScreen()

    int len = arrLen;
    while (len--)
    {
        bool swaps = false;
        for (int i = 0; i <= len; ++i)
        {
            if (OBJECT_ON_SCREEN) continue;
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
    #undef OBJECT_ON_SCREEN
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



HeroLazerStorage::HeroLazerStorage(const int capacity): ArrStorageABC(capacity)
{
    if (init == false) return;
    //storage = new ElementaryObject*[capacity] {nullptr};
}



LongLazer* HeroLazerStorage::operator[](const int index)
{
    if (index < 0 || index >= counter) return nullptr;
    return static_cast<LongLazer*>(storage[index]);
}

bool HeroLazerStorage::Push(ElementaryObject* ob)
{
    if (counter >= storageCapacity) return false;
    storage[counter++] = static_cast<LongLazer*>(ob);
    return true;
}

void HeroLazerStorage::Move(bool& flag_toStartSort)
{
    for (int i = 0; i < counter; ++i)
    {
        static_cast<LongLazer*>(storage[i])->Move();
        if (static_cast<LongLazer*>(storage[i])->OnScreen() == false)
            flag_toStartSort = true;
    }
}

void HeroLazerStorage::Show(const Sdl* sdl) const
{
    for (int i = 0; i < counter; ++i)
    {
        if (storage[i])
            static_cast<LongLazer*>(storage[i])->Show(sdl);
    }
}


AlienFleet_oneStorage::AlienFleet_oneStorage(const int capacity): 
                                                ArrStorageABC(capacity)
{
    if (init == false) return;
    //storage = new ElementaryObject*[capacity] {nullptr};
}

PlainAlien_t1* AlienFleet_oneStorage::operator[](const int index)
{
    if (index < 0 || index >= counter) return nullptr;
    return static_cast<PlainAlien_t1*>(storage[index]);
}

bool AlienFleet_oneStorage::Push(ElementaryObject* ob)
{
    if (counter >= storageCapacity) return false;
    storage[counter++] = static_cast<PlainAlien_t1*>(ob);
    return true;
}





ObjectsStore::ObjectsStore(const tc* collection)
{
    if (!collection)
    {
        init = false; return;
    }
    tcollection = collection;
    heroLazerStorage = new (std::nothrow) 
                                        HeroLazerStorage{HERO_LAZERSTORAGE_CAP};
    if (!heroLazerStorage)
    {
        init = false; return;
    }
    alienFleetOneStorage = new (std::nothrow) 
                                    AlienFleet_oneStorage{ALIENFLEET_ONE_CAP};
    if (!alienFleetOneStorage)
    {
        init = false; return;
    }
    if (!makeAlienFleetOne(collection))
    {
        init = false; return;
    }
}

ObjectsStore::~ObjectsStore()
{
    tcollection = nullptr;
    delete heroLazerStorage;
    heroLazerStorage = nullptr;
    delete alienFleetOneStorage;
    alienFleetOneStorage = nullptr;
}

void ObjectsStore::MoveHeroLazers()
{
    bool flag_StartSort = false;
    heroLazerStorage->Move(flag_StartSort);
    if (flag_StartSort)
    {
        heroLazerStorage->Sort(HERO_LAZERSTORAGE_CAP, heroLazerStorage->GetCounter());
    }
}

void ObjectsStore::ShowHeroLazers(const Sdl* sdl) const
{
    heroLazerStorage->Show(sdl);
}

bool ObjectsStore::MakeHeroLazer(const plot* start)
{
    /*Если это первый выстрел*/
    if (heroLazerStorage->GetCounter() == 0)
    {
        return heroLazerStorage->Push(new LongLazer{start, dir::right,
                                    &tcollection->Pictures()[tn::blue_laser]});
    }
  
    #define COUNTER heroLazerStorage->GetCounter()
    #define PREVLAZER heroLazerStorage->operator[](COUNTER - 1)
    #define PREVLAZER_X PREVLAZER->GetLazer_x()
    #define PREVLAZER_W PREVLAZER->GetLazer_w()
    /*Если предыдущий выстрел слишком близко, то ничего не делаем*/
    if ( (PREVLAZER_X - start->x) < PREVLAZER_W * 3) return false;
    return heroLazerStorage->Push(new LongLazer{start, dir::right,
                                    &tcollection->Pictures()[tn::blue_laser]});


    #undef PREVLAZER_X
    #undef PREVLAZER_W
    #undef PREVLAZER
    #undef COUNTER
}