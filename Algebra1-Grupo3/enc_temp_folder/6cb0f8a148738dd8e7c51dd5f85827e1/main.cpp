#include <iostream>
#include "Squares.h"

using namespace std;

void SearchCorner(Line line[], Line corners[]);
bool lineIntersecctions(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Line intersections[]);

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	int currentLine = 0;
	int currentPosition = START;
	bool lineDrawn = false;

	Vector2 mousePos;

	Line myLines[LINES_AMOUNT];
	Line Intersect[MAX_CORNERS];

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

		SearchCorner(myLines, Intersect);

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

void SearchCorner(Line line[], Line corners[])
{
	Line auxLine;

	for (int i = 0; i < LINES_AMOUNT; i++)
	{
		auxLine = line[i];

		for (int j = 0; j < LINES_AMOUNT; j++)
		{
			if (auxLine.Start.x != line[j].Start.x && auxLine.Start.y != line[j].Start.y)
			{
				lineIntersecctions(auxLine.Start.x, auxLine.Start.y, auxLine.Finish.x, auxLine.Finish.y, line[j].Start.x, line[j].Start.y, line[j].Finish.x, line[j].Finish.y, corners);
			}
		}
	}
}

bool lineIntersecctions(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Line intersections[])
{

	// calculate the distance to intersection point
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{

		// optionally, draw a circle where the lines meet
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		intersections->Intersect.x = intersectionX;
		intersections->Intersect.y = intersectionY;

		DrawCircle(intersectionX, intersectionY, 5, RED);

		return true;
	}
	return false;
}