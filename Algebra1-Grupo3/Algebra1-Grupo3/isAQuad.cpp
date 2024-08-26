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
	if (IsSameCorner(thisCorner, firstCorner)|| segments == 4) 
	{
		if (IsSameCorner(thisCorner, firstCorner) && segments == 4)
		{
			isSameQuad = false;
			for (int quad = 0; quad < quadList.size(); quad++)
			{
				isSameQuad = IsSameQuad(quadCorners, quadList, quad);
			}
			if(!isSameQuad)
			{
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

	//Which line does it belong to
	int line = 0;
	for (; line < LINES_AMOUNT; line++)
	{
		for (int corner = 0; corner < lines[line].CornersAmount; corner++)
		{
			if (IsSameCorner(lines[line].Corners[corner], thisCorner))
			{
				segments += 1;
				quadCorners[segments] = thisCorner; 

				//next corner
				for (int nextCorner = 0; nextCorner < lines[line].CornersAmount; nextCorner++)
				{
					IsAQuad(lines, firstCorner, lines[line].Corners[nextCorner], quadCorners, segments, quadList);
				}

			}
		}
	}
}

bool IsSameQuad(Vector2* quadCorners, std::vector<Quad> QuadList, int quad)
{
	return IsSameCorner(QuadList[quad].C1, quadCorners[0])
		&& IsSameCorner(QuadList[quad].C2, quadCorners[1])
		&& IsSameCorner(QuadList[quad].C3, quadCorners[2])
		&& IsSameCorner(QuadList[quad].C4, quadCorners[3]);
}

bool IsSameCorner(const Vector2& corner1, const Vector2& corner2)
{
	return corner1.x < FLT_EPSILON + corner2.x && corner1.x > corner2.x - FLT_EPSILON
		&& corner1.y < FLT_EPSILON + corner2.y && corner1.y > corner2.y - FLT_EPSILON;
}
