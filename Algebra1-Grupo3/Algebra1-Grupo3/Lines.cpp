#include "Lines.h"

Vector2 GetMouseCoord()
{
	Vector2 vector;

	vector.x = GetMouseX();
	vector.y = GetMouseY();

	return vector;
}

void DrawLine(Line line, Line lines[LINES_AMOUNT], int currentPos)
{
	DrawLine(line.Start.x, line.Start.y, line.Finish.x, line.Finish.y, RED);

	lines[currentPos] = line;
}

void CheckLinesCreated(Line myLines[], int& currentPosition, int& currentLine)
{
	Vector2 mousePos;

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
}

void DrawLines(Line myLines[])
{
	for (int i = 0; i < LINES_AMOUNT; i++)
	{
		if (myLines[i].Done)
		{
			DrawLine(myLines[i], myLines, i);
		}
	}
}