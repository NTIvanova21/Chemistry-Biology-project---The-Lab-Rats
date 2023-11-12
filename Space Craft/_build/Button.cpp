#include "Button.h"
#include "window.h"

Button* Button::instance = nullptr;

void Button::DrawButton(Rectangle rect) {
	DrawRectangleRec(rect, colorButtons);
}

bool Button::IsClicked(Rectangle rect) {
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rect);
}

void Button::DrawButtonsShop(Rectangle rect, bool completed, int type) {
	if (type == 1) {
		if (completed) {
			DrawRectangleRec(rect, GREEN);
		}
		else {
			DrawRectangleRec(rect, DARKGREEN);
		}
	}
	if (type == 2) {
		if (completed) {
			DrawRectangleRec(rect, YELLOW);
		}
		else {
			DrawRectangleRec(rect, GOLD);
		}
	}
	if (type == 3) {
		if (completed) {
			DrawRectangleRec(rect, BLUE);
		}
		else {
			DrawRectangleRec(rect, DARKBLUE);
		}
	}
	
}
