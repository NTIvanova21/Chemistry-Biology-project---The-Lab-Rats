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

private:
	static Renderer* instance;

	Image icon;
	Texture2D map;
};