#include "Application.h"
#include <iostream>
#include "Corners.h"

using namespace std;

void MainLoop()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	int currentLine = 0;
	int currentPosition = START;
	Line lines[LINES_AMOUNT];

	InitWindow(screenWidth, screenHeight, "Quad test");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		CheckLinesCreated(lines, currentPosition, currentLine);

		SearchCorner(lines, currentLine);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Clic on two positions!", 20, 20, 20, WHITE);

		DrawLines(lines);

		DrawCorners(lines);
		
		EndDrawing();
	}

	CloseWindow();
}