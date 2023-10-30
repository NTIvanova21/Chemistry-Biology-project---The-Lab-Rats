#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

void Renderer::Start() {
	//;( nqma da se opravim
}

void Renderer::LoadTextures() {
	background = LoadTexture("../resources/background.png");
}

void Renderer::Update() {
	BeginDrawing();

		ClearBackground(WHITE);
		GameManager::GetInstance()->GetCharacter()->DrawCharacter();

	EndDrawing();
}