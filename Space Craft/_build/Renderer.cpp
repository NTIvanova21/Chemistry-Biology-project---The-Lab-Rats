#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Start() {
	
}

void Renderer::LoadTextures() {
	mainBackground = LoadTexture("../resources/main_background.png");
}

void Renderer::Update() {
	BeginDrawing();

		ClearBackground(WHITE);
		GameManager::GetInstance()->GetCharacter()->DrawCharacter();

	EndDrawing();
}