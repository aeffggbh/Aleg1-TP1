#include <iostream>
#include "Squares.h"

using namespace std;

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	int currentLine = 0;
	int currentPosition = START;
	bool lineDrawn = false;

	Vector2 mousePos;

	Line myLines[LINES_AMOUNT];

	InitWindow(screenWidth, screenHeight, "Quad test");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mousePos = GetMouseCoord();


			if (!myLines[currentLine].Done && currentLine < LINES_AMOUNT)
			{
				if (currentPosition == START)
				{
					myLines[currentLine].Start.x = mousePos.x;
					myLines[currentLine].Start.y = mousePos.y;
					currentPosition = FINISH;
				}
				else
				{
					myLines[currentLine].Finish.x = mousePos.x;
					myLines[currentLine].Finish.y = mousePos.y;
					currentPosition = START;
					myLines[currentLine].Done = true;
					currentLine++;
				}
			}
		}

		BeginDrawing();

		ClearBackground(BLACK);
		DrawText("Clic on two positions!", 20, 20, 20, WHITE);

		for (int i = 0; i < LINES_AMOUNT; i++)
		{
			if (myLines[i].Done)
			{
				DrawLine(myLines[i], myLines, i);
			}
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}

