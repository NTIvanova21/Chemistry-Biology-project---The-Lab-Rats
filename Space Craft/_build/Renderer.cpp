#include "Renderer.h"
#include "Button.h"
#include "window.h"
#include "Manager.h"
#include "Character.h"

Renderer* Renderer::instance = nullptr;
Button buttons;

bool menu = true, info = false, playing = true, spaceship = false, shop = false, glass = false, plastic = false, paper = false;

int earthStage = 1, counterGlass = 0, counterPlastic = 0, counterPaper = 0;
std::string counterGlass1, counterPlastic1, counterPaper1;

void Renderer::LoadTextures() {
	mainMenu = LoadTexture("../resources/main_menu.png");
	map = LoadTexture("../resources/main_background.png");
	infoMenu = LoadTexture("../resources/info.png");
	spaceshipMap = LoadTexture("../resources/spaceship_background.png");
	shopMap = LoadTexture("../resources/spaceship_menu.png");
	earthStage1 = LoadTexture("../resources/earth_first_stage.png");
	earthStage2 = LoadTexture("../resources/earth_second_stage.png");
	earthStage3 = LoadTexture("../resources/earth_third_stage.png");
	earthClean = LoadTexture("../resources/clean_earth.png");

	icon = LoadImage("../resources/icon.png");

	fonty = LoadFont("../resources/candy_beans.otf");

	SetWindowIcon(icon);
}

void Renderer::BackgroundMovement(Texture2D map,float& scrollback) {

	auto character = GameManager::GetInstance()->GetCharacter();
	Vector2 current = character->GetPosition();

	if (IsKeyDown(KEY_D)){

		if (scrollback <= 0.0f && scrollback >= -1078.0f) {
			
			if (current.x >= 700) {
				scrollback -= 4.0f;
			}
			else {
				current.x += 4;
				character->SetPosition(current);
			}
			
		}
		else if (current.x <= 1600) {
			current.x += 4;
			character->SetPosition(current);
		}
	}
	if (IsKeyDown(KEY_A)){

		if (scrollback <= -4.0f && scrollback >= -1265.0f){
			if (current.x <= 700) {
				scrollback += 4.0f;
			}
			else {
				current.x -= 4;
				character->SetPosition(current);
			}
		}
		else if (current.x >= 120){
			current.x -= 4;
			character->SetPosition(current);
		}
	}
}
// 1 - glass, 2- plastic, 3 - paper;
void Renderer::ShopCounter(int* counter, bool* completed, Rectangle button, const char* current, int type) {

	if (*counter < 5) {
		Button::GetInstance()->DrawButtonsShop(button, false, type);
		DrawTextEx(fonty, current, {button.x + 65, button.y - 10}, 90, 10, WHITE);
		DrawTextEx(fonty, "/5", { button.x + 135, button.y - 10 }, 90, 10, WHITE);
	}
	else {
		if (Button::GetInstance()->IsClicked(button) && !*completed) {
			*completed = true;
			earthStage++;
		}
		if (*completed) {
			Button::GetInstance()->DrawButtonsShop(button, true, type);
			DrawTextEx(fonty, "Completed", { button.x + 8, button.y }, 60, 10, WHITE);
		}
		else {
			Button::GetInstance()->DrawButtonsShop(button, true, type);
			DrawTextEx(fonty, current, { button.x + 65, button.y - 10 }, 90, 10, WHITE);
			DrawTextEx(fonty, "/5", { button.x + 135, button.y - 10 }, 90, 10, WHITE);
		}
	}
}
void Renderer::Update() {

	auto character = GameManager::GetInstance()->GetCharacter();
	Vector2 current = character->GetPosition();

	BeginDrawing();

	ClearBackground(WHITE);
	if (menu) {
		DrawTexture(mainMenu, 0, 0, WHITE);

		Button::GetInstance()->DrawButton(buttons.mainMenuButtons[0]);
		Button::GetInstance()->DrawButton(buttons.mainMenuButtons[1]);
		Button::GetInstance()->DrawButton(buttons.mainMenuButtons[2]);

		DrawTextEx(fonty, "Play", { buttons.mainMenuButtons[0].x + 60, buttons.mainMenuButtons[0].y - 4 }, 100, 10, WHITE);
		DrawTextEx(fonty, "Info", { buttons.mainMenuButtons[1].x + 60, buttons.mainMenuButtons[1].y - 4 }, 100, 10, WHITE);
		DrawTextEx(fonty, "Quit", { buttons.mainMenuButtons[2].x + 60, buttons.mainMenuButtons[2].y - 4 }, 100, 10, WHITE);

		if (Button::GetInstance()->IsClicked(buttons.mainMenuButtons[0])) {
			menu = false;
		}
		if (Button::GetInstance()->IsClicked(buttons.mainMenuButtons[1])) {
			info = true;
			menu = false;
		}
		if (Button::GetInstance()->IsClicked(buttons.mainMenuButtons[2])) {
			Manager::GetInstance()->Close();
		}
	}
	else if (info) {
		DrawTexture(infoMenu, 0, 0, WHITE);
		Button::GetInstance()->DrawButton(buttons.back);
		DrawTextEx(fonty, "Back", { buttons.back.x + 10, buttons.back.y - 5 }, 100, 10, WHITE);
		if (Button::GetInstance()->IsClicked(buttons.back)) {
			menu = true;
			info = false;
		}
	}
	else if (playing) {
		BackgroundMovement(map, scrollback);
		DrawTextureEx(map, { scrollback }, 0.0f, 1.0f, WHITE);
		GameManager::GetInstance()->GetCharacter()->DrawCharacter();
		if (IsKeyPressed(KEY_E) && current.x <= 116) {
			playing = false;
			spaceship = true;
			current.x = 1650;
			character->SetPosition(current);
		}
	}
	else if (spaceship) {
		DrawTexture(spaceshipMap, 0, 0, WHITE);

		GameManager::GetInstance()->GetCharacter()->DrawCharacter();
		if (IsKeyDown(KEY_D)) {

			if (current.x <= 1650) {
				GameManager::GetInstance()->GetCharacter()->Walk(1);
				current.x += 10;
				character->SetPosition(current);
			}

		}
		if (IsKeyDown(KEY_A)) {

			if (current.x >= 200) {
				GameManager::GetInstance()->GetCharacter()->Walk(-1);
				current.x -= 10;
				character->SetPosition(current);
			}

		}
		if (IsKeyPressed(KEY_E) && current.x >= 1650) {

			current.x = 116;
			character->SetPosition(current);

			playing = true;
			spaceship = false;
		}
		if (IsKeyPressed(KEY_E) && current.x <= 200) {
			spaceship = false;
			shop = true;
		}
	}
	else if (shop) {

		DrawTexture(shopMap, 0, 0, WHITE);
		counterGlass1 = std::to_string(counterGlass);
		counterPlastic1 = std::to_string(counterPlastic);
		counterPaper1 = std::to_string(counterPaper);
		ShopCounter(&counterGlass, &glass, buttons.shopButtons[0], counterGlass1.c_str(), 1 );
		ShopCounter(&counterPlastic, &plastic, buttons.shopButtons[1], counterPlastic1.c_str(), 2) ;
		ShopCounter(&counterPaper, &paper, buttons.shopButtons[2], counterPaper1.c_str(), 3);
			
		if (IsKeyPressed(KEY_E)) {
			counterGlass++;
		}
		Button::GetInstance()->DrawButton(buttons.arrow);

		if (Button::GetInstance()->IsClicked(buttons.arrow)) {
			shop = false;
			spaceship = true;
		}

		DrawTextEx(fonty, "<=", { buttons.arrow.x, buttons.arrow.y - 20  }, 100, 10, WHITE);
			
		if (earthStage == 1) {
			DrawTexture(earthStage1, 20, 30, WHITE);
		}
		else if (earthStage == 2) {
			DrawTexture(earthStage2, 20, 30, WHITE);
		}
		else if (earthStage == 3) {
			DrawTexture(earthStage3, 20, 30, WHITE);
		}
		else if (earthStage == 4) {
			DrawTexture(earthClean, 20, 30, WHITE);
		}
		else {
			DrawTexture(mainMenu, 0, 0, WHITE);
			DrawTextEx(fonty, "YOU WON MAN", { 720, 600 }, 100, 10, WHITE);
		}
	}
		
	EndDrawing();
}