#include "Squares.h"

void DrawLine(Line line, Line lines[LINES_AMOUNT])
{
	DrawLine(line.Start.x, line.Start.y, line.Finish.x, line.Finish.y, RED);

	lines[LINE_POS] = line;
}