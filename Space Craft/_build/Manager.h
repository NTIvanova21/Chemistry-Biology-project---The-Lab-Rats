#pragma once

#include "raylib.h"
#include "window.h"
#include "Renderer.h"

class Manager {
public:
	static Manager* GetInstance() {
		if (instance == nullptr) {
			instance = new Manager;
		}
		return instance;
	}
	void Initialize();

	void Start();

	void Update();

	bool ShouldWindowClose();

	void Close();

private:
	static Manager* instance;

	Renderer* renderer;

	GameManager* gameManager;

	bool shouldWindowClose = false;
};