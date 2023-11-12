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
			DrawRectangleRec(rect, greenAfter);
		}
		else {
			DrawRectangleRec(rect, greenBefore);
		}
	}
	if (type == 2) {
		if (completed) {
			DrawRectangleRec(rect, yellowAfter);
		}
		else {
			DrawRectangleRec(rect, yellowBefore);
		}
	}
	if (type == 3) {
		if (completed) {
			DrawRectangleRec(rect, blueAfter);
		}
		else {
			DrawRectangleRec(rect, blueBefore);
		}
	}
	
	
}

void Button::DrawFinishButton(Rectangle rect){
	DrawRectangleRec(rect, finishButton);
} 

