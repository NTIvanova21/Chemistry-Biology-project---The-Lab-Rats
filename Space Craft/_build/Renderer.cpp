#include "Renderer.h"
#include "Button.h"
#include "window.h"
#include "Manager.h"
#include "Character.h"

Renderer* Renderer::instance = nullptr;
Button buttons;

bool menu = true, info = false;

void Renderer::LoadTextures() {
	mainMenu = LoadTexture("../resources/main_menu.png");
	map = LoadTexture("../resources/main_background.png");
	infoMenu = LoadTexture("../resources/info.png");
	icon = LoadImage("../resources/icon.png");
	fonty = LoadFont("../resources/candy_beans.otf");

	SetWindowIcon(icon);
}

void Renderer::BackgroundMovement(Texture2D map,float& scrollback) {

	auto character = GameManager::GetInstance()->GetCharacter();
	Vector2 current = character->GetPosition();
	if (IsKeyDown(KEY_D)){

		if (scrollback <= 0.0f && scrollback >= -1078.0f){
			scrollback -= 4.0f;
		}
		else if (scrollback <= -1078.0f){
			if (current.x <= 1600){
				current.x += 4;
				character->SetPosition(current);
			}
		}
	}

	if (IsKeyDown(KEY_A)){

		if (scrollback <= -4.0f && scrollback >= -1265.0f){
			scrollback += 4.0f;
		}
		else if (current.x >= 200){
			current.x -= 4;
			character->SetPosition(current);
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
			
			DrawTextEx(fonty, "Play", { buttons.start.x + 60, buttons.start.y - 4 }, 100, 10, WHITE);
			DrawTextEx(fonty, "Info", { buttons.info.x + 60, buttons.info.y - 4 }, 100, 10, WHITE);
			DrawTextEx(fonty, "Quit", { buttons.quit.x + 60, buttons.quit.y - 4 }, 100, 10, WHITE);

			if (Button::GetInstance()->IsClicked(buttons.start)) {
				menu = false;
			}
			if (Button::GetInstance()->IsClicked(buttons.info)) {
				info = true;
				menu = false;
			}
			if (Button::GetInstance()->IsClicked(buttons.quit)) {
				Manager::GetInstance()->Close();
			}
		}
		else if(info) {
			DrawTexture(infoMenu, 0, 0, WHITE);
			Button::GetInstance()->DrawButton(buttons.back);
			DrawText("Back", buttons.back.x + 27, buttons.back.y + 20, 50, WHITE);
			if (Button::GetInstance()->IsClicked(buttons.back)) {
				menu = true;
				info = false;
			}
			
			
		}
		else {
			BackgroundMovement(map, scrollback);
			DrawTextureEx(map, { scrollback }, 0.0f, 1.0f, WHITE);
			GameManager::GetInstance()->GetCharacter()->DrawCharacter();
		}
		
		

	EndDrawing();
}