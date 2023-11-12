#include "Button.h"
#include "window.h"

Button* Button::instance = nullptr;

void Button::DrawButton(Rectangle rect) {

	// Draw buttons
	DrawRectangleRec(rect, colorButtons);
}

bool Button::IsClicked(Rectangle rect) {

	// Check if the leff button of the mouse if pressed
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rect);
}

void Button::DrawButtonsShop(Rectangle rect, bool completed, int type) {

	// Draw the counters' buttons

	if (type == 1) {

		if (completed) {

			// Change the color when completed
			DrawRectangleRec(rect, greenAfter);
		}
		else {
			DrawRectangleRec(rect, greenBefore);
		}
	}
	if (type == 2) {

		if (completed) {

			// Change the color when completed
			DrawRectangleRec(rect, yellowAfter);
		}
		else {
			DrawRectangleRec(rect, yellowBefore);
		}
	}
	if (type == 3) {

		if (completed) {

			// Change the color when completed
			DrawRectangleRec(rect, blueAfter);
		}
		else {
			DrawRectangleRec(rect, blueBefore);
		}
	}
	
	
}

void Button::DrawFinishButton(Rectangle rect){
	// Draw the finish button
	DrawRectangleRec(rect, finishButton);
} 

void Button::DrawArrowButton(Rectangle rect) {
	// Draw the arrow button
	DrawRectangleRec(rect, arrowButton);
}