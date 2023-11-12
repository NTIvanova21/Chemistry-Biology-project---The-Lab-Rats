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

	void DrawButtonsShop(Rectangle rect, bool completed, int type);

	bool IsClicked(Rectangle rect);

	Rectangle mainMenuButtons[3] = {
		{ 810,450,300,100 },
		{ 810,650,300,100 },
		{ 810,850,300,100 }
	};
	Rectangle back = { 50,50,200,80 };
	Rectangle arrow = { 37,50,100,55 };
	Rectangle shopButtons[3] = {
		{1400,230,300,70 },
		{1400,430,300,70 },
		{1400,630,300,70 }
	};
	Rectangle completed = { 1400,430,300,70 };
private:
	static Button* instance;
	
};