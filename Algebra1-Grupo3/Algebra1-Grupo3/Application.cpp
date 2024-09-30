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
	std::vector<Quad> quadList;
	Vector2 quadCorners[4];
	bool quadLooked = false;

	InitWindow(screenWidth, screenHeight, "Quad test");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		if(currentLine < LINES_AMOUNT)
		{
			CheckLinesCreated(lines, currentPosition, currentLine);

			SearchCorner(lines, currentLine);
		}
		else if(!quadLooked)
		{
			for(int i = 0; i < LINES_AMOUNT; i++)
			{
				for (auto corner : lines[i].Corners)
				{
					IsAQuad(lines, corner, quadList, quadCorners);
				}
			}
			quadLooked = true;
		}
		std::cout << quadList.size() << std::endl;
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Clic on two positions!", 20, 20, 20, WHITE);

		DrawLines(lines);

		DrawCorners(lines);
		
		EndDrawing();
	}

	CloseWindow();
}