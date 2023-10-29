#include <raylib.h>
#include <iostream>
#include <vector>
#include "Map.h"

int main() {

	std::vector<Colorizations::Map::Civilization> civilizations;

	Colorizations::Map::Civilization none;
	none.color = { 150, 150, 150, 255 };
	none.money = 0;

	Colorizations::Map::Civilization orange;
	orange.color = { 255, 150, 0, 255 };
	orange.money = 100;
	Colorizations::Map::Civilization red;
	red.color = { 255, 0, 0, 255 };
	red.money = 100;
	Colorizations::Map::Civilization blue;
	blue.color = { 0,0,255, 255 };
	blue.money = 100;
	Colorizations::Map::Civilization green;
	green.color = { 0,255,0, 255 };
	green.money = 100;

	civilizations.push_back(none);
	civilizations.push_back(orange);
	civilizations.push_back(red);
	civilizations.push_back(blue);
	civilizations.push_back(green);

	std::vector<Colorizations::Map::Tile> map;

	Colorizations::Map::Tile emptyTile;
	emptyTile.civilization = 0;
	emptyTile.type = Colorizations::Map::SUB_PLAINS;
	for (int i = 0; i < 100 * 100; i++) {
		map.push_back(emptyTile);
	}

	Vector2 viewOffset = { 0,0 };

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(1280, 720, "Colorizations");
	SetTargetFPS(60);
	float zoom = 1;
	while (!WindowShouldClose()) {
		SetExitKey(0);

		BeginDrawing();
		ClearBackground(WHITE);
		
		if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
			viewOffset.x += GetMouseDelta().x;
			viewOffset.y += GetMouseDelta().y;
			SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
		}
		else {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}

		zoom += GetMouseWheelMove()/10;
		if (zoom < 0.01f) zoom = 0.1f;
		Vector2 mousePos = GetMousePosition();
		bool alreadySelected = false;
		int selectedTile = -1;
		for (int i = 0; i < map.size(); i++) {
			float lineoffset = 0;
			if ((int)(i / 100) * 100 % 200) lineoffset = 8.5;
			// printf("%i - %i\n", (int)100 + ((i * 15)), (int)((i / 100) * 10));
			DrawPoly({ viewOffset.x + ((float)100 + ((i % 100) * 17.5f) + lineoffset) * zoom, viewOffset.y + ((float)100 + (int)((i / 100) * 15)) * zoom }, 6, 10 * zoom, 0, civilizations.at(map.at(i).civilization).color);
			DrawPolyLines({ viewOffset.x + ((float)100+((i%100) * 17.5f) + lineoffset) * zoom, viewOffset.y + ((float)100+(int)((i / 100) * 15)) * zoom }, 6, 10*zoom, 0, BLACK);
			if(mousePos.x < (viewOffset.x + ((float)100 + ((i % 100) * 17.5f) + lineoffset+8) * zoom)){
				if (mousePos.x > (viewOffset.x + ((float)100 + ((i % 100) * 17.5f) + lineoffset - 8) * zoom)) {
					if (mousePos.y < (viewOffset.y + ((float)100 + (int)((i / 100) * 15) + 8) * zoom)) {
						if (mousePos.y > (viewOffset.y + ((float)100 + (int)((i / 100) * 15) - 8) * zoom)) {
							if(!alreadySelected){
								DrawPoly({ viewOffset.x + ((float)100 + ((i % 100) * 17.5f) + lineoffset) * zoom, viewOffset.y + ((float)100 + (int)((i / 100) * 15)) * zoom }, 6, 10 * zoom, 0, RAYWHITE);
								selectedTile = i;
							}
							alreadySelected = true;
						}
					}
				}
			}
		}
		DrawFPS(0, 0);
		EndDrawing();
		if (selectedTile != -1) {
			if (IsKeyDown(KEY_ONE)) {
				map.at(selectedTile).civilization = 1;
			}
			if (IsKeyDown(KEY_TWO)) {
				map.at(selectedTile).civilization = 2;
			}
			if (IsKeyDown(KEY_THREE)) {
				map.at(selectedTile).civilization = 3;
			}
			if (IsKeyDown(KEY_FOUR)) {
				map.at(selectedTile).civilization = 4;
			}
			if (IsKeyDown(KEY_ZERO)) {
				map.at(selectedTile).civilization = 0;
			}
		}
	}

	CloseWindow();
}