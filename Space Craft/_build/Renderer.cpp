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
			DrawTexture(map, 0, 0, WHITE);
			GameManager::GetInstance()->GetCharacter()->DrawCharacter();
		}
		
		

	EndDrawing();
}