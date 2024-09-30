#include "Squares.h"
bool IsSameCornerForQuad(const Vector2& corner1, const Vector2& corner2);

bool IsAQuad(Line lines[], Vector2 thisCorner, std::vector<Quad>& quadList, Vector2 quadCorners[4],
             Vector2 firstCorner, int segments)
{
    bool isSameQuad = false;

    //check whether the new quad is in the quadlist
    for (Quad& quad : quadList)
    {
        isSameQuad = IsSameQuad(quadCorners, quad);
    }

    if (!isSameQuad)
    {
        //First corner set up
        if (segments == 0)
        {
            firstCorner = thisCorner;
        }


        //Exit Clause
        if ((IsSameCorner(thisCorner, firstCorner) || segments == 4) && segments > 0)
        {
            if (IsSameCorner(thisCorner, firstCorner) && segments == 4)
            {
                for (Quad& quad : quadList)
                {
                    isSameQuad = IsSameQuad(quadCorners, quad);
                }
                if (!isSameQuad && quadCorners[0].x < 800 && quadCorners[0].x > 0)
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
            return false;
        }

        // it iterates over all lines that have this corner in them
        for (int line = 0; line < LINES_AMOUNT; line++)
        {
            for (auto corner : lines[line].Corners)
            {
                if (!IsSameCorner(corner, thisCorner) && segments < 4)
                {
                    quadCorners[segments] = thisCorner;
                    segments += 1;

                    // iterate with next corner
                    for (int nextCorner = 0; nextCorner < lines[line].Corners.size(); nextCorner++)
                    {
                        IsAQuad(lines, lines[line].Corners[nextCorner], quadList, quadCorners, firstCorner, segments);
                    }
                }
            }
        }
    }
    return false;
}

bool IsSameQuad(Vector2 quad1[], Quad& quad2)
{
    for (int i = 0; i < 4; i++)
    {
        if(IsSameCornerForQuad(quad2.C1, quad1[0 + i % 4])
            && IsSameCornerForQuad(quad2.C2, quad1[1 + i % 4])
            && IsSameCornerForQuad(quad2.C3, quad1[2 + i % 4])
            && IsSameCornerForQuad(quad2.C4, quad1[3 + i % 4]))
        {
            return true;
        }
    }
    return false;
}

bool IsSameCornerForQuad(const Vector2& corner1, const Vector2& corner2)
{
    constexpr float margin = 2;
    return corner1.x < margin + corner2.x && corner1.x > corner2.x - margin
        && corner1.y < margin + corner2.y && corner1.y > corner2.y - margin;
}