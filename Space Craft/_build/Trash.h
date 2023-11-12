#pragma once

#include "raylib.h"
#include <cmath>
#include "GameManager.h"

class Trash {
public:
	// Initialise constructor
	Trash(Texture texture, Vector2 position, float rotation, int type);

	void Update(float scrollback);

	void DrawTrash(float scrollback);

	bool IsClose(Vector2 position, float scrollback);

	int GetType();

	bool IsTaken();

private:
	Vector2 position;

	Texture texture;

	float rotation;

	bool taken = false;

	int type;
};