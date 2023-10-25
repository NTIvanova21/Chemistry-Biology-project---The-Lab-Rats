#include <iostream>
#include "raylib.h"

int main(){
	InitWindow(903, 331, "game");
	while (!WindowShouldClose()) {
		BeginDrawing();
		DrawRectangle(5, 5, 5, 5, BLUE);
		EndDrawing();
	}
	CloseWindow();
}