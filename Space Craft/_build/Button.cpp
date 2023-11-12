#include "Button.h"
#include "window.h"

Button* Button::instance = nullptr;

void Button::DrawButton(Rectangle rect) {
	DrawRectangleRec(rect, colorButtons);
}

bool Button::IsClicked(Rectangle rect) {
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rect);
}

void Button::DrawButtonGlass(Rectangle rect, bool completed) {
	if (completed) {
		DrawRectangleRec(rect, GREEN);
	}
	else {
		DrawRectangleRec(rect, DARKGREEN);
	}
}

void Button::DrawButtonPlastic(Rectangle rect) {
	DrawRectangleRec(rect, YELLOW);
}

void Button::DrawButtonPaper(Rectangle rect) {
	DrawRectangleRec(rect, BLUE);
}