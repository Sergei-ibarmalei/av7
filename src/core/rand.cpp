#include "rand.h"

int getRand(int a, int b)
{
    return (a + rand() % (b - a + 1));
}