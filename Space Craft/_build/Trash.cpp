#include "Trash.h"

Trash::Trash(Texture type, Vector2 position, float rotation) {
	this->type = type;
	this->position = position;
	this->rotation = rotation;
}

void Trash::DrawTrash(float scrollback) {
	position.x += scrollback;
	DrawTextureEx(type, position, rotation, 1, WHITE);
}

bool Trash::IsClose(Vector2 position) {
	float distance = abs(abs(position.x - this->position.x) - 112);
	return distance < 60;
}

void Trash::Update() {
	auto character = GameManager::GetInstance()->GetCharacter();
	if (IsClose(character->GetPosition())) {
	}
}