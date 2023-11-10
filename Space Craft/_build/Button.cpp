#include "Button.h"
#include "window.h"

Button* Button::instance = nullptr;

void Button::DrawButton(Rectangle rect) {
	DrawRectangleRec(rect, colorButtons);
}

bool Button::IsClicked(Rectangle rect) {
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rect);
}