#pragma once

#include "Character.h"

class GameManager {
public:
    static GameManager* GetInstance() {
        if (instance == nullptr) {
            instance = new GameManager;
        }
        return instance;
    }

    void Update();

    Character* GetCharacter();

private:
    static GameManager* instance;

    Character* character = new Character("../resources/walk.png");
};