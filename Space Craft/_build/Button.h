#pragma once

#include "raylib.h"

class Button {

public:
	static Button* GetInstance() {
		if (instance == nullptr) {
			instance = new Button;
		}
		return instance;
	}

	void DrawButton(Rectangle rect);

	bool IsClicked(Rectangle rect);

	Rectangle start = { 810,450,300,100 };
	Rectangle info = { 810,650,300,100 };
	Rectangle quit = { 810,850,300,100 };
	Rectangle back = { 50,50,200,80 };

private:
	static Button* instance;
	
};