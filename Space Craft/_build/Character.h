#pragma once

#include <string>
#include <cmath>
#include "raylib.h"

struct Character {
public:
    Character(std::string characterWalkPath);

    void DrawCharacter();

    void Walk(int direction);

    void ResetFrames();

private:
    Vector2 position = { 300, 200 };
    float movementSpeed = 5;

    Rectangle frameRec;
    Texture2D characterWalk;

    bool isFlipped = false;

    float time = 0.0f;
    int frame = 0;
};