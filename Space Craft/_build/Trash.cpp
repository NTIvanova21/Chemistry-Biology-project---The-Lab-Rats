#include "Trash.h"


Trash::Trash(Texture texture, Vector2 position, float rotation, int type) {

	// Allocate texture, position, rotation and type
	this->texture = texture;
	this->position = position;
	this->rotation = rotation;
	this->type = type;
}

void Trash::DrawTrash(float scrollback) {

	// Check if the trash is removed
	if (taken) {
		return;
	}

	DrawTextureEx(texture, { position.x + scrollback, position.y }, rotation, 1, WHITE);
}

bool Trash::IsClose(Vector2 position, float scrollback) {

	// Check the proximity of player to trash entity
	float distance = abs(abs((position.x - scrollback) - this->position.x) - 112);
	return distance < 60;
}

void Trash::Update(float scrollback) {

	auto character = GameManager::GetInstance()->GetCharacter();

	// Allow player to pick up trash
	if (IsClose(character->GetPosition(), scrollback) && IsKeyPressed(KEY_E)) {
		taken = true;
	}
}

int Trash::GetType() {

	// Returns the type of trash that was collected
	return type;
}

bool Trash::IsTaken() {

	// Return if the trash is collected or not
	return taken;
}