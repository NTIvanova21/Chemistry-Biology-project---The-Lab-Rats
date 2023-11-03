#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Start() {
	
}

void Renderer::LoadTextures() {
	map = LoadTexture("../resources/main_background.png");
}

void Renderer::Update() {
	BeginDrawing();

		ClearBackground(WHITE);
		DrawTexture(map, 0, 0, WHITE);
		GameManager::GetInstance()->GetCharacter()->DrawCharacter();

	EndDrawing();
}