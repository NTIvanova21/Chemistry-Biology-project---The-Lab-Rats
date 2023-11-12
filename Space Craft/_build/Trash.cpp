#include "Trash.h"

Trash::Trash(Texture texture, Vector2 position, float rotation, int type) {
	this->texture = texture;
	this->position = position;
	this->rotation = rotation;
	this->type = type;
}

void Trash::DrawTrash(float scrollback) {

	if (taken) {
		return;
	}

	DrawTextureEx(texture, { position.x + scrollback, position.y }, rotation, 1, WHITE);
}

bool Trash::IsClose(Vector2 position, float scrollback) {
	float distance = abs(abs((position.x - scrollback) - this->position.x) - 112);
	return distance < 60;
}

void Trash::Update(float scrollback) {
	auto character = GameManager::GetInstance()->GetCharacter();
	if (IsClose(character->GetPosition(), scrollback) && IsKeyPressed(KEY_E)) {
		taken = true;
	}
}

int Trash::GetType() {
	return type;
}

bool Trash::IsTaken() {
	return taken;
}