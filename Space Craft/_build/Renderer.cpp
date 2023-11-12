#include "Renderer.h"
#include "Manager.h" 

Renderer* Renderer::instance = nullptr;
Button buttons;

//Load textures, images, font and icon

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
	glassTexture = LoadTexture("../resources/glass.png");
	plasticTexture = LoadTexture("../resources/plastic.png");
	paperTexture = LoadTexture("../resources/paper.png");
	arrow = LoadTexture("../resources/arrow.png");
	endScreen = LoadTexture("../resources/end_screen.png");
	cutScene = LoadTexture("../resources/cut_scene.png");
	reversedArrow = LoadTexture("../resources/arrow_reversed.png");

	frameRec = { 0, 0, (float)cutScene.width / 4, (float)cutScene.height };

	icon = LoadImage("../resources/icon.png");

	fonty = LoadFont("../resources/candy_beans.otf");

	SetWindowIcon(icon);
}

void Renderer::LoadTrash() {

	std::vector<int> trashList = { 1, 3, 2, 1, 2, 2, 1, 2, 3, 1, 3, 3 };

	// Randomise where the trash spawn

	std::random_shuffle(trashList.begin(), trashList.end());

	int collectiveDistance = 700;

	for (size_t i = 0; i < trashList.size(); i++) {

		int distance = rand() % 100 + 100;
		int vertical = rand() % 50;
		float rotate = (rand() % 200 - 100) / 10;

		collectiveDistance += distance;

		Vector2 position = { collectiveDistance, 850 + vertical };

		// Spawn trash
		if (trashList.at(i) == 1) {
			AddTrash({ glassTexture, position, rotate, 1 });
		}
		if (trashList.at(i) == 2) {
			AddTrash({ plasticTexture, position, rotate, 2});
		}
		if (trashList.at(i) == 3) {
			AddTrash({ paperTexture, position, rotate, 3 });
		}

	}
}

// Add the trash to the vector
void Renderer::AddTrash(Trash trash) {
	this->trash.push_back(trash);
}

// Make trash stationary
void Renderer::DrawTrash() {
	for (auto& i : this->trash) {
		i.DrawTrash(scrollback);
		i.Update(scrollback);
	}
}

// Update each counter when the coresponding trash is taken
void Renderer::CountTrash() {
	int tempGlass = 0, tempPlastic = 0, tempPaper = 0;
	for (auto& i : this->trash) {
		if (!i.IsTaken()) {
			continue;
		}
		if (i.GetType() == 1) {
			tempGlass++;
		}
		if (i.GetType() == 2) {
			tempPlastic++;
		}
		if (i.GetType() == 3) {
			tempPaper++;
		}
	}

	counterGlass = tempGlass;
	counterPlastic = tempPlastic;
	counterPaper = tempPaper;
}

// Move the backgound when the character is moving

void Renderer::BackgroundMovement(Texture2D map, float& scrollback) {

	auto character = GameManager::GetInstance()->GetCharacter();
	Vector2 current = character->GetPosition();

	// Make character move right
	if (IsKeyDown(KEY_D)) {

		if (scrollback <= 0.0f && scrollback >= -1078.0f) {

			if (current.x >= 750) {
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

	// Make character move left
	if (IsKeyDown(KEY_A)) {

		if (scrollback <= -4.0f && scrollback >= -1265.0f) {
			if (current.x <= 750) {
				scrollback += 4.0f;
			}
			else {
				current.x -= 4;
				character->SetPosition(current);
			}
		}
		else if (current.x >= 120) {
			current.x -= 4;
			character->SetPosition(current);
		}
	}
}


void Renderer::ShopCounter(int* counter, bool* completed, Rectangle button, const char* current, int type) {

	// Show the counter of the trash
	if (*counter < 4) {

		Button::GetInstance()->DrawButtonsShop(button, false, type);
		DrawTextEx(fonty, current, { button.x + 65, button.y - 10 }, 90, 10, WHITE);
		DrawTextEx(fonty, "/4", { button.x + 135, button.y - 10 }, 90, 10, WHITE);
	}
	else {

		
		if (Button::GetInstance()->IsClicked(button) && !*completed) {
			*completed = true;
			earthStage++;
		}

		// Display completed status on click
		if (*completed) {
			Button::GetInstance()->DrawButtonsShop(button, true, type);
			DrawTextEx(fonty, "Completed", { button.x + 8, button.y }, 60, 10, WHITE);
		}
		else {
			Button::GetInstance()->DrawButtonsShop(button, true, type);
			DrawTextEx(fonty, current, { button.x + 65, button.y - 10 }, 90, 10, WHITE);
			DrawTextEx(fonty, "/4", { button.x + 135, button.y - 10 }, 90, 10, WHITE);
		}
	}
}
void Renderer::Update() {
	//Get the character's position
	auto character = GameManager::GetInstance()->GetCharacter();
	Vector2 current = character->GetPosition();

	BeginDrawing();

	ClearBackground(WHITE);

	if (menu) {

		DrawTexture(mainMenu, 0, 0, WHITE);

		// Draw menu buttons
		Button::GetInstance()->DrawButton(buttons.mainMenuButtons[0]);
		Button::GetInstance()->DrawButton(buttons.mainMenuButtons[1]);
		Button::GetInstance()->DrawButton(buttons.mainMenuButtons[2]);

		// Draw the text for the menu buttons
		DrawTextEx(fonty, "Play", { buttons.mainMenuButtons[0].x + 60, buttons.mainMenuButtons[0].y - 4 }, 100, 10, WHITE);
		DrawTextEx(fonty, "Info", { buttons.mainMenuButtons[1].x + 60, buttons.mainMenuButtons[1].y - 4 }, 100, 10, WHITE);
		DrawTextEx(fonty, "Quit", { buttons.mainMenuButtons[2].x + 60, buttons.mainMenuButtons[2].y - 4 }, 100, 10, WHITE);

		if (Button::GetInstance()->IsClicked(buttons.mainMenuButtons[0])) {
			// Start the cutscene
			menu = false;
			cutscene = true;
		}
		if (Button::GetInstance()->IsClicked(buttons.mainMenuButtons[1])) {
			// Open info
			info = true;
			menu = false;
		}
		if (Button::GetInstance()->IsClicked(buttons.mainMenuButtons[2])) {
			// Quit the game
			Manager::GetInstance()->Close();
		}
	}
	else if (info) {
		// Draw the info
		DrawTexture(infoMenu, 0, 0, WHITE);

		Button::GetInstance()->DrawButton(buttons.back);

		// Draw the back button
		DrawTextEx(fonty, "Back", { buttons.back.x + 10, buttons.back.y - 5 }, 100, 10, WHITE);

		// Draw text for info
		DrawTextEx(fonty, "INFO", { 885, 23 }, 100, 10, BLACK);
		DrawTextEx(fonty, "Backstory", { 765, 153 }, 90, 10, BLACK);
		DrawTextEx(fonty, "You are an astronaut garbage collector and your job is to collect the", { 165, 250 }, 55, 3, BLACK);
		DrawTextEx(fonty, "differend types of trash on the Moon so that way you can clean both the", { 165, 300 }, 55, 3, BLACK);
		DrawTextEx(fonty, "Moons surface and the Earths orbit.", { 165, 350 }, 55, 3, BLACK);

		DrawTextEx(fonty, "How to play", { 765, 450 }, 90, 5, BLACK);
		DrawTextEx(fonty, "move right -> press D", { 165, 600 }, 55, 3, BLACK);
		DrawTextEx(fonty, "move left -> press A", { 165, 650 }, 55, 3, BLACK);
		DrawTextEx(fonty, "collect an item -> press E", { 165, 700 }, 55, 3, BLACK);
		DrawTextEx(fonty, "enter or exit the spaceship -> press E", { 165, 750 }, 55, 3, BLACK);




		if (Button::GetInstance()->IsClicked(buttons.back)) {
			// Return to the menu
			menu = true;
			info = false;
		}
	}
	else if (cutscene) {
		if (frames <= 3) {

			// Change frames
			frameRec.x = frames * cutScene.width / 4;

			// Start with the first cutscese
			DrawTextureRec(cutScene, frameRec, { 0,0 }, WHITE);

			Button::GetInstance()->DrawArrowButton(buttons.next);

			// Add arrow for the next cutscene
			DrawTexture(reversedArrow, buttons.next.x + 6, buttons.next.y + 3, WHITE);

			if (Button::GetInstance()->IsClicked(buttons.next)) 
			{
				frames++;
				
			}
			// Add text to the cutscenes
			switch (frames) {
				case 0:
					DrawTextEx(fonty, "The year is 2078, the Earth is already so polluted that people cannot live there. Many of them are trying to", { 40, 880 }, 40, 3, BLACK);
					DrawTextEx(fonty, "find a way out, but they don't have the financial means and most are exposed to death.", { 40, 930 }, 40, 3, BLACK);
					break;
				case 1:
					DrawTextEx(fonty, "Rich people have left Earth and built nice houses on the moon. There they live peacefully with their families", { 40, 880 }, 40, 3, BLACK);
					DrawTextEx(fonty, "while ordinary people suffer on Earth.", { 40, 930 }, 40, 3, BLACK);
					break;
				case 2:
					DrawTextEx(fonty, "You are the chosen one to help all humans return to Earth and continue their lives there. Your task", { 40, 880 }, 40, 3, BLACK);
					DrawTextEx(fonty, "is to clean up their mess as quickly as possible and save planet Earth.", { 40, 930 }, 40, 3, BLACK);
					break;
			}

		}
		else {
			// Start gameplay

			cutscene = false;
			playing = true;
		}

	}
	else if (playing) {
		// Make the backgound move
		BackgroundMovement(map, scrollback);

		DrawTextureEx(map, { scrollback }, 0.0f, 1.0f, WHITE);
		
		// Add the trash
		DrawTrash();
		CountTrash();

		GameManager::GetInstance()->GetCharacter()->DrawCharacter();

		// Enter the spaceship
		if (IsKeyPressed(KEY_E) && current.x <= 116) {

			playing = false;
			spaceship = true;
			current.x = 1650;

			character->SetPosition(current);
		}
	}
	else if (spaceship) {
		// Draw spaseship
		DrawTexture(spaceshipMap, 0, 0, WHITE);

		GameManager::GetInstance()->GetCharacter()->DrawCharacter();

		// Make the character move right
		if (IsKeyDown(KEY_D)) {

			if (current.x <= 1650) {

				GameManager::GetInstance()->GetCharacter()->Walk(1);
				current.x += 10;
				character->SetPosition(current);
			}

		}
		// Make the character move left
		if (IsKeyDown(KEY_A)) {

			if (current.x >= 200) {

				GameManager::GetInstance()->GetCharacter()->Walk(-1);
				current.x -= 10;
				character->SetPosition(current);
			}

		}
		// Exit the spaceship
		if (IsKeyPressed(KEY_E) && current.x >= 1650) {

			current.x = 116;
			character->SetPosition(current);

			playing = true;
			spaceship = false;
		}
		// Enter shop
		if (IsKeyPressed(KEY_E) && current.x <= 200) {

			spaceship = false;
			shop = true;
		}
	}
	else if (shop) {

		// Draw shop
		DrawTexture(shopMap, 0, 0, WHITE);

		// Draw the Earth's stages
		if (earthStage <= 3) {

			// Add the text for the trash
			DrawTextEx(fonty, "Glass", { 1400, 180 }, 60, 5, WHITE);
			DrawTextEx(fonty, "Plastic", { 1400, 380 }, 60, 5, WHITE);
			DrawTextEx(fonty, "Paper", { 1400, 580 }, 60, 5, WHITE);

			// Add the trash counters
			counterGlass1 = std::to_string(counterGlass);
			counterPlastic1 = std::to_string(counterPlastic);
			counterPaper1 = std::to_string(counterPaper);

			ShopCounter(&counterGlass, &glass, buttons.shopButtons[0], counterGlass1.c_str(), 1);
			ShopCounter(&counterPlastic, &plastic, buttons.shopButtons[1], counterPlastic1.c_str(), 2);
			ShopCounter(&counterPaper, &paper, buttons.shopButtons[2], counterPaper1.c_str(), 3);
		}
		else {

			Button::GetInstance()->DrawFinishButton(buttons.completed);

			// Draw the finish button
			DrawTextEx(fonty, "Finish", { buttons.completed.x + 25, buttons.completed.y - 10 }, 90, 10, WHITE);

			if (Button::GetInstance()->IsClicked(buttons.completed)) {
				earthStage++;
			}
		}

		Button::GetInstance()->DrawButton(buttons.arrow);

		if (Button::GetInstance()->IsClicked(buttons.arrow)) {
			// Exit the shop and enter the spaceship
			shop = false;
			spaceship = true;
		}

		DrawTexture(arrow, buttons.arrow.x, buttons.arrow.y - 3, WHITE);

		// Change current stage of Earth
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
			// Display end screen
			DrawTexture(endScreen, 0, 0, WHITE);

		}
	}

	EndDrawing();
}