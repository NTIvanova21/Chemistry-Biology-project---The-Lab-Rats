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

	void LoadTextures();

	void Update();

	void BackgroundMovement(Texture2D map, float& scrollback);

	void ShopCounter(int* counter, bool* stage, Rectangle button, const char* current, int type);

private:
	static Renderer* instance;

	Font fonty;

	Image icon;

	Texture2D map;
	Texture2D mainMenu;
	Texture2D infoMenu;
	Texture2D spaceshipMap;
	Texture2D shopMap;
	Texture2D earthStage1;
	Texture2D earthStage2;
	Texture2D earthStage3;
	Texture2D earthClean;

	float scrollback = 0.0f;

};