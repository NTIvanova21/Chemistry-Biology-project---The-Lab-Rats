#pragma once

#include "raylib.h"
#include "GameManager.h"
#include "Trash.h"
#include "Button.h"
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

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

	void LoadTrash();

	void DrawTrash();

	void AddTrash(Trash trash);

	void CountTrash();

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
	Texture2D glassTexture;
	Texture2D paperTexture;
	Texture2D plasticTexture;
	Texture2D arrow;
	Texture2D endScreen;
	Texture2D cutScene;

	std::vector<Trash> trash;

	float scrollback = 0.0f;

	bool menu = true, info = false, playing = true, spaceship = false, shop = false, glass = false, plastic = false, paper = false;

	int earthStage = 1, counterGlass = 0, counterPlastic = 0, counterPaper = 0, frames = 0;

	std::string counterGlass1, counterPlastic1, counterPaper1;

};