#include "Squares.h"

Vector2 GetMouseCoord()
{
	Vector2 vector;

	vector.x = GetMouseX();
	vector.y = GetMouseY();

	return vector;
}

void DrawLine(Line line, Line lines[LINES_AMOUNT])
{
	DrawLine(line.Start.x, line.Start.y, line.Finish.x, line.Finish.y, RED);

	lines[LINE_POS] = line;
}

bool IsAQuad(Line lines[LINES_AMOUNT])
{
	return false;
}