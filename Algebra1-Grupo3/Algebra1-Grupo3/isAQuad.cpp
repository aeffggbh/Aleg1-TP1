#include "Squares.h"

bool IsAQuad(Line lines[], Vector2 firstCorner, Vector2 thisCorner, Vector2 quadCorners[4], int segments, Quad& returnedQuad)
{
	//First corner set up
	if(segments == 0)
	{
		firstCorner = thisCorner;
	}

	//Exit Clause
	if(thisCorner.x == firstCorner.x && firstCorner.y == thisCorner.y) //todo add epsilon
	{
		if (segments == 4) 
		{
			returnedQuad = { quadCorners[0], quadCorners[1], quadCorners[2], quadCorners[3] };
			return true;
		}
		else if(segments > 0 && segments < 4)
		{
			return false;
		}
	}

	//Which line does it belong to
	int line = 0;
	for(bool found = false; line < LINES_AMOUNT && !found; line++)
	{
		for(int corner = 0; corner < lines[line].CornersAmount; corner++)
		{
			if(lines[line].Corners[corner].x == thisCorner.x && lines[line].Corners[corner].y == thisCorner.y)
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
		IsAQuad(lines, firstCorner, lines[line].Corners[corner], quadCorners, segments, returnedQuad);
	}
}