#include "Character.h"

// Load character sprite
Character::Character(std::string characterWalkPath) {
    this->characterWalk = LoadTexture(characterWalkPath.c_str());

    frameRec = { 0, 0, (float)characterWalk.width / 8, (float)characterWalk.height };
}

// Return the position
Vector2 Character::GetPosition() {

    return position;
}

void Character::SetPosition(Vector2 position) {
    this->position = position;
}


void Character::DrawCharacter() {

    // Draw character
    frameRec.x = (float)frame * (float)characterWalk.width / 8;

    frameRec.width = abs(frameRec.width);
    // Change the direction of the character
    if (isFlipped) {
        frameRec.width *= -1;
    }

    DrawTextureRec(characterWalk, frameRec, position, WHITE);
}

void Character::Walk(int direction) {
    
    // Make the character walk
    isFlipped = direction == 1;
    time += GetFrameTime();

    if (time >= 0.12f) {
        time = 0.0f;
        frame++;
    }

    frame %= 8; 
}

void Character::ResetFrames() {

    // Reset the frames to zero
    frame = 0;
}