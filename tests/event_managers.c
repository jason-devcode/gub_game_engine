#include "../include/managers/event_manager.h"

void message()
{
    puts("hola");
}

int main()
{
    EventManager manager;
    initializeEventManager(&manager, 32);

    addEventListener(&manager, 16, message);

    triggerEvent(manager, 16);

    removeEventListener(&manager, 16, message);
    freeEventManager(&manager, true);

    return EXIT_SUCCESS;
}