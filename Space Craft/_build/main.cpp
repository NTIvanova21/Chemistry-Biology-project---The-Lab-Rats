#include "Manager.h"

int main() {

    Manager* manager = Manager::GetInstance();

    manager->Initialize();

    while (!manager->ShouldWindowClose())
    {
        manager->Update();
    }

    CloseWindow();
}