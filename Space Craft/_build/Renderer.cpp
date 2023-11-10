#include "Renderer.h"
#include "Button.h"
#include "window.h"
#include "Manager.h"

Renderer* Renderer::instance = nullptr;
Button buttons;

bool menu = true;

void Renderer::Start() {
	
}

void Renderer::LoadTextures() {
	mainMenu = LoadTexture("../resources/main_menu.png");
	map = LoadTexture("../resources/main_background.png");
	icon = LoadImage("../resources/icon.png");

	SetWindowIcon(icon);
}

void Renderer::BackgroundMovement(Texture2D map,float& scrollback) {

	if (IsKeyDown(KEY_D) && (scrollback >= -1065.0f && scrollback <= 5.0f)) {

		scrollback -= 4.0f;
		if (scrollback <= -map.width * 2) {
			scrollback = 0;
		}
	}

	////Moves The Background And Prevents Mickey From Going To Far To The Left
	if (IsKeyDown(KEY_A) && (scrollback <= -10.0f && scrollback >= -1265.0f)) {

		scrollback += 4.0f;
		if (scrollback <= -map.width * 2) {
			scrollback = 0;
		}
	}
}
void Renderer::Update() {
	BeginDrawing();

		ClearBackground(WHITE);
		if (menu) {
			DrawTexture(mainMenu, 0, 0, WHITE);

			Button::GetInstance()->DrawButton(buttons.start);	
			Button::GetInstance()->DrawButton(buttons.info);
			Button::GetInstance()->DrawButton(buttons.quit);

			DrawText("Play", buttons.start.x + 40, buttons.start.y - 4, 100, WHITE);
			DrawText("Info", buttons.info.x + 40, buttons.info.y - 4, 100, WHITE);
			DrawText("Quit", buttons.quit.x + 40, buttons.quit.y - 4, 100, WHITE);

			if (Button::GetInstance()->IsClicked(buttons.start)) {
				menu = false;
			}
			if (Button::GetInstance()->IsClicked(buttons.info)) {
				//info
				//back button?
			}
			if (Button::GetInstance()->IsClicked(buttons.quit)) {
				Manager::GetInstance()->Close();
			}
		}
		else {
			BackgroundMovement(map, scrollback);
			DrawTextureEx(map, { scrollback }, 0.0f, 1.0f, WHITE);
			GameManager::GetInstance()->GetCharacter()->DrawCharacter();
		}
		
		

	EndDrawing();
}