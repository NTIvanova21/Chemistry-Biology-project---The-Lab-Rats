#pragma once

#include "raylib.h"
#include <string>
#include "GameManager.h"

class Renderer {
public:
	static Renderer* GetInstance() {
		if (instance == nullptr) {
			instance = new Renderer;
		}
		return instance;
	}

	void Start();

	void LoadTextures();

	void Update();

	void BackgroundMovement(Texture2D map, float& scrollback);

private:
	static Renderer* instance;

	Font fonty;
	Image icon;
	Texture2D map;
	Texture2D mainMenu;
	Texture2D infoMenu;

	float scrollback = 0.0f;

};