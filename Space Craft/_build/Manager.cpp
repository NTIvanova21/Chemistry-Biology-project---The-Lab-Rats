#include "Manager.h"

Manager* Manager::instance = nullptr;

void Manager::Initialize() {

	InitWindow(screenWidth, screenHeight, screenTitle);
	SetTargetFPS(60);
	Start();
}

void Manager::Start() {
	renderer = Renderer::GetInstance();
	gameManager = GameManager::GetInstance();

	renderer->LoadTextures();
	renderer->LoadTrash();
}

void Manager::Update() {
	renderer->Update();
	gameManager->Update();
}

bool Manager::ShouldWindowClose() {

	return WindowShouldClose() || shouldWindowClose;
}

void Manager::Close() {

	shouldWindowClose = true;
}