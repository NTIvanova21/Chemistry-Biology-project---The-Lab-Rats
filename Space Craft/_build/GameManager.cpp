#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Update() {
    // -1 - Left, 1 - Right

    if (IsKeyDown(KEY_A)) {
        character->Walk(-1);
    }
    else if (IsKeyDown(KEY_D)) {
        character->Walk(1);
    }
    else {
        character->ResetFrames();
    }
}

Character* GameManager::GetCharacter() {
    return character;
}