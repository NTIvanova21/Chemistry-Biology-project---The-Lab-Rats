#include "Manager.h"

Manager* Manager::instance = nullptr;

void Manager::Initialize() {

	//Initialize window
	InitWindow(screenWidth, screenHeight, screenTitle);
	ToggleFullscreen();
	SetTargetFPS(60);
	Start();
}

void Manager::Start() {

	// Get instance for renderer and game manager
	renderer = Renderer::GetInstance();
	gameManager = GameManager::GetInstance();

	renderer->LoadTextures();
	renderer->LoadTrash();
}

void Manager::Update() {

	// Call Update function
	renderer->Update();
	gameManager->Update();
}

bool Manager::ShouldWindowClose() {

	return WindowShouldClose() || shouldWindowClose;
}

void Manager::Close() {

	shouldWindowClose = true;
}