#pragma once

#include "raylib.h"
#include "GameManager.h"
#include "Trash.h"
#include "Button.h"
#include <vector>
#include <string>
#include <algorithm>

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

	// Define font, image, textures and rectanges

	Font fonty;

	Image icon;

	Texture2D maps[2];
	Texture2D menus[3];
	Texture2D infoMenu;
	Texture2D earthStages[4];
	Texture2D typesOfTrash[3];
	Texture2D endScreen;
	Texture2D cutScene;
	Texture2D arrow;
	Texture2D reversedArrow;

	Rectangle frameRec;

	std::vector<Trash> trash;

	float scrollback = 0.0f;
	
	bool menu = true, info = false, playing = true, spaceship = false, shop = false, glass = false, plastic = false, paper = false, cutscene = false;

	int earthStage = 1, counterGlass = 0, counterPlastic = 0, counterPaper = 0, frames = 0;

	std::string counterGlass1, counterPlastic1, counterPaper1;

};