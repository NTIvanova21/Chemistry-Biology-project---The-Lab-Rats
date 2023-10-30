#include "Character.h"

Character::Character(std::string characterWalkPath) {
    this->characterWalk = LoadTexture(characterWalkPath.c_str());

    frameRec = { 0, 0, (float)characterWalk.width / 8, (float)characterWalk.height };
}

void Character::DrawCharacter() {

    frameRec.x = (float)frame * (float)characterWalk.width / 8;

    frameRec.width = abs(frameRec.width);
    if (isFlipped) {
        frameRec.width *= -1;
    }

    DrawTextureRec(characterWalk, frameRec, position, WHITE);
}

// -1 - Left, 1 - Right
void Character::Walk(int direction) {
    isFlipped = direction == 1;
    time += GetFrameTime();

    if (time >= 0.12f) {
        time = 0.0f;
        frame++;
    }

    frame %= 8; // Replace with maxFrames

    position.x += movementSpeed * direction;
}

void Character::ResetFrames() {
    frame = 0;
}