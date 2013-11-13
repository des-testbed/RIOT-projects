#include "cppMix.hpp"

cppMix::cppMix()
{
    greet();
}

cppMix::~cppMix()
{
    printf("Im shutting down!\n");
}

void cppMix::sayHello(void)
{
    printf("Hello!\n");
}

void cppMix::greet(void)
{
    printf("Im starting!\n");
}


