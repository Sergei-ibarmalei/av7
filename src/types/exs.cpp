#include "exs.h"

GameEx::GameEx(const ex::gameErrs& err)
{
    ge = err;
}

void GameEx::GameExMsg()
{
    switch (ge)
    {
        case ex::RENDERER_IS_ABSENT:
        {
            std::cout << "Renderer is absent or renderer is nullptr\n";
            break;
        }
        case ex::CANNOT_ALLOCATE_MEM_GAMEFONTS:
        {
            std::cout << "Canot allocate memory for game fonts.\n";
            break;
        }
        case ex::CANNOT_OPEN_FONT:
        {
            std::cout << "Cannot open global font.\n";
            break;
        }
        case ex::CANNOT_ALLOCATE_MEM_STRINGTEXTURES:
        {
            std::cout << "Cannot allocate memory for string textures.\n";
            break;
        }
        case ex::CANNOT_CREATE_PICTURETEXTURE:
        {
            std::cout << 
        }
    }
}