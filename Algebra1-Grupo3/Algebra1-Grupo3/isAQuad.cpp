#include "Squares.h"

bool IsAQuad(Line lines[], Vector2 firstCorner, Vector2 thisCorner, Vector2 quadCorners[4], int segments,
             std::vector<Quad>
             QuadList)
{
	bool isSameQuad = false;
	int quadsAmount = QuadList.size() / sizeof(Quad);

	//First corner set up
	if (segments == 0)
	{
		firstCorner = thisCorner;
	}

	//Exit Clause
	if (IsSameCorner(thisCorner, firstCorner)|| segments == 4) //todo add epsilon
	{
		if (IsSameCorner(thisCorner, firstCorner) && segments == 4)
		{
			isSameQuad = false;
			for (int quad = 0; quad < QuadList.size(); quad++)
			{
				isSameQuad = IsSameQuad(quadCorners, QuadList, quad);
			}
			if(!isSameQuad)
			{
				QuadList.resize(sizeof(Quad));

				QuadList[quadsAmount].C1.x = quadCorners[0].x;
				QuadList[quadsAmount].C2.x = quadCorners[1].x;
				QuadList[quadsAmount].C3.x = quadCorners[2].x;
				QuadList[quadsAmount].C4.x = quadCorners[3].x;

				QuadList[quadsAmount].C1.y = quadCorners[0].y;
				QuadList[quadsAmount].C2.y = quadCorners[1].y;
				QuadList[quadsAmount].C3.y = quadCorners[2].y;
				QuadList[quadsAmount].C4.y = quadCorners[3].y;

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
	for (bool found = false; line < LINES_AMOUNT && !found; line++)
	{
		for (int corner = 0; corner < lines[line].CornersAmount; corner++)
		{
			if (IsSameCorner(lines[line].Corners[corner], thisCorner))
			{
				found = true;
			}
		}
	}

	segments += 1;
	quadCorners[segments] = thisCorner;

	//next corner
	for (int corner = 0; corner < lines[line].CornersAmount; corner++)
	{
		IsAQuad(lines, firstCorner, lines[line].Corners[corner], quadCorners, segments, QuadList);
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
