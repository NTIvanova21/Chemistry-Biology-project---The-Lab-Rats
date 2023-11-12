#pragma once

#include "raylib.h"
#include <cmath>
#include "GameManager.h"

class Trash {
public:
	Trash(Texture type, Vector2 position, float rotation);

	void Update();

	void DrawTrash(float scrollback);

	bool IsClose(Vector2 position);

private:
	Vector2 position;

	Texture type;

	float rotation;
};