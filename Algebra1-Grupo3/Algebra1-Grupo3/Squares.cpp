#include "Squares.h"

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
		for (int corner = 0; corner < lines[line].CornersAmount; corner++)
		{
			if (!IsSameCorner(lines[line].Corners[corner], thisCorner))
			{
				segments += 1;
				quadCorners[segments] = thisCorner;

				// iterate with next corner
				for (int nextCorner = 0; nextCorner < lines[line].CornersAmount; nextCorner++)
				{
					IsAQuad(lines, firstCorner, lines[line].Corners[nextCorner], quadCorners, segments, quadList);
				}

			}
		}
	}
}

bool IsSameQuad(Vector2 quad1[], Quad& quad2)
{
	return IsSameCorner(quad2.C1, quad1[0])
		&& IsSameCorner(quad2.C2, quad1[1])
		&& IsSameCorner(quad2.C3, quad1[2])
		&& IsSameCorner(quad2.C4, quad1[3]);
}