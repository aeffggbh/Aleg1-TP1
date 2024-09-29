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
	Vector2 QuadVectors[4];

	InitWindow(screenWidth, screenHeight, "Quad test");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		CheckLinesCreated(lines, currentPosition, currentLine);

		SearchCorner(lines);

		BeginDrawing();

		for(int i = 0; i < currentLine; i++)
		{
			for (int j = 0; j < lines[i].CornersAmount; j++)
			{
				IsAQuad(lines, lines[i].Corners[j], lines[i].Corners[j], QuadVectors, 0, quadList);
			}
		}

		cout << quadList.size() << endl;

		ClearBackground(BLACK);

		DrawText("Clic on two positions!", 20, 20, 20, WHITE);

		DrawLines(lines);
		
		EndDrawing();
	}

	CloseWindow();
}