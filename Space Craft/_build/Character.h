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

    void SetPosition(Vector2 position);

    Vector2 GetPosition();

private:

    Vector2 position = { 200, 690 };
    
    float movementSpeed = 5;

    Rectangle frameRec;
    Texture2D characterWalk;

    bool isFlipped = true;

    float time = 0.0f;
    int frame = 0;
};