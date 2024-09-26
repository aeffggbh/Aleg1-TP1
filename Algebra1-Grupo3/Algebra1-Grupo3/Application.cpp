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
	Line myLines[LINES_AMOUNT];

	InitWindow(screenWidth, screenHeight, "Quad test");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		CheckLinesCreated(myLines, currentPosition, currentLine);

		BeginDrawing();

		SearchCorner(myLines);

		ClearBackground(BLACK);

		DrawText("Clic on two positions!", 20, 20, 20, WHITE);

		DrawLines(myLines);
		
		EndDrawing();
	}

	CloseWindow();
}