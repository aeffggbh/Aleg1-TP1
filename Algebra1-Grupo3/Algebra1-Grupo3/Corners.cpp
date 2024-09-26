#include "Corners.h"

void SearchCorner(Line lines[])
{
	for (int i = 0; i < LINES_AMOUNT; i++)
		for (int j = i + 1; j < LINES_AMOUNT; j++)
			LineIntersections(lines[i], lines[j]);
}

void LineIntersections(Line& line_A, Line& line_B)
{
	// y = m x + B

	const float step = 0.0005f;

	const float m_A = FindM(line_A);
	float b_A = FindB(line_A, m_A);
	const float m_B = FindM(line_B);
	float b_B = FindB(line_B, m_B);

	//traverses the line
	for(float x = line_A.Start.x; x < line_A.Finish.x; x += step)
	{
		if((m_A * x + b_A - b_B) / m_B == line_B.Start.y)
		{
			AddCorner();
			break;
		}
	}

		
}

void AddCorner(Line& line, const int newY, const int newX)
{
	line.Corners[0].x = newX;
	line.Corners[0].y = newY;
	line.CornersAmount++;
}

float FindM(const Line& line)
{
	//The length in y / x of a line
	return (line.Finish.x - line.Start.x) / (line.Finish.y - line.Start.y);
}

float FindB(const Line& line, const float m)
{
	//The height of the intersections of the lines
	return line.Start.y - m * line.Start.x;
}



bool IsSameCorner(const Vector2& corner1, const Vector2& corner2)
{
	return corner1.x < FLT_EPSILON + corner2.x && corner1.x > corner2.x - FLT_EPSILON
		&& corner1.y < FLT_EPSILON + corner2.y && corner1.y > corner2.y - FLT_EPSILON;
}
