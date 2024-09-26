#include "Corners.h"

void SearchCorner(Line line[])
{
	Line auxLine;

	for (int i = 0; i < LINES_AMOUNT; i++)
	{
		auxLine = line[i];

		for (int j = 0; j < LINES_AMOUNT; j++)
		{
			if (auxLine.Start.x != line[j].Start.x && auxLine.Start.y != line[j].Start.y)
			{
				LineIntersections(auxLine.Start.x, auxLine.Start.y, auxLine.Finish.x, auxLine.Finish.y, line[j].Start.x, line[j].Start.y, line[j].Finish.x, line[j].Finish.y, line->Corners);
			}
		}
	}
}

void LineIntersections(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Vector2 Corners[])
{
	Line auxCorner;

	// calculate the distance to intersection point
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		// optionally, draw a circle where the lines meet
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		AddCorner(Corners, intersectionY, intersectionX);

		DrawCircle(intersectionX, intersectionY, 5, RED);
	}
}

void AddCorner(Vector2 Corners[], int newY, int newX)
{
	bool cornerDone = false;

	for (int i = 0; i < MAX_CORNERS; i++)
	{
		if (!cornerDone)
		{
			Corners[i].x = newX;
			Corners[i].y = newY;
			cornerDone = true;
			return;
		}
	}

}

bool IsSameCorner(const Vector2& corner1, const Vector2& corner2)
{
	return corner1.x < FLT_EPSILON + corner2.x && corner1.x > corner2.x - FLT_EPSILON
		&& corner1.y < FLT_EPSILON + corner2.y && corner1.y > corner2.y - FLT_EPSILON;
}