#include "Squares.h"
#include <cmath>

bool IsAQuad(Line lines[], Vector2 firstCorner, Vector2 thisCorner, Vector2 quadCorners[4], int segments,
	std::vector<Quad> quadList)
{
	bool isSameQuad = false;

	//First corner set up
	if (segments == 0)
	{
		firstCorner = thisCorner;
	}

	//Exit Clause
	if (IsSameCorner(thisCorner, firstCorner) || segments == 4)
	{
		if (IsSameCorner(thisCorner, firstCorner) && segments == 4)
		{
			//check whether the new quad is in the quadlist
			isSameQuad = false;
			for (Quad& quad : quadList)
			{
				isSameQuad = IsSameQuad(quadCorners, quad);
			}
			if (!isSameQuad)
			{
				//append new quad
				Quad newQuad;

				newQuad.C1.x = quadCorners[0].x;
				newQuad.C2.x = quadCorners[1].x;
				newQuad.C3.x = quadCorners[2].x;
				newQuad.C4.x = quadCorners[3].x;

				newQuad.C1.y = quadCorners[0].y;
				newQuad.C2.y = quadCorners[1].y;
				newQuad.C3.y = quadCorners[2].y;
				newQuad.C4.y = quadCorners[3].y;

				quadList.push_back(newQuad);

				return true;
			}
		}
		if (segments > 0 && segments < 4)
		{
			return false;
		}
		return false;
	}

	// it iterates over all lines that have this corner in them
	for (int line = 0; line < LINES_AMOUNT; line++)
	{
		for (auto corner : lines[line].Corners)
		{
			if (!IsSameCorner(corner, thisCorner))
			{
				segments += 1;
				quadCorners[segments] = thisCorner;

				// iterate with next corner
				for (int nextCorner = 0; nextCorner < lines[line].Corners.size(); nextCorner++)
				{
					IsAQuad(lines, firstCorner, lines[line].Corners[nextCorner], quadCorners, segments, quadList);
				}

			}
		}
	}
	return false;
}

bool IsSameQuad(Vector2 quad1[], Quad& quad2)
{
	return IsSameCorner(quad2.C1, quad1[0])
		&& IsSameCorner(quad2.C2, quad1[1])
		&& IsSameCorner(quad2.C3, quad1[2])
		&& IsSameCorner(quad2.C4, quad1[3]);
}

float Distance(Vector2 a, Vector2 b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float CalculatePerimeter(Quad quad)
{
	float d1 = Distance(quad.C1, quad.C2); // Distancia entre c1 y c2
	float d2 = Distance(quad.C2, quad.C3); // Distancia entre c2 y c3
	float d3 = Distance(quad.C3, quad.C4); // Distancia entre c3 y c4
	float d4 = Distance(quad.C4, quad.C1); // Distancia entre c4 y c1

	return d1 + d2 + d3 + d4;
}

float CalculateQuadArea(Quad quad)
{
	return 0.5f * abs(quad.C1.x * quad.C2.y + quad.C2.x * quad.C3.y + quad.C3.x * quad.C4.y + quad.C4.x * quad.C1.y -
					(quad.C2.x * quad.C1.y + quad.C3.x * quad.C2.y + quad.C4.x * quad.C3.y + quad.C1.x * quad.C4.y));
}