#include "Engine.h"

int main()
{
    Engine engine;
    if (engine.Initialize())
    {
        engine.Loop();
    }

    return 0;
}