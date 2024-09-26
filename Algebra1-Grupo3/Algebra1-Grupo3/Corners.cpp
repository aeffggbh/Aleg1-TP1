#include "Corners.h"

void SearchCorner(Line lines[])
{
    Line auxLine;

    for (int i = 0; i < LINES_AMOUNT; i++)
    {
        auxLine = lines[i];

        for (int j = 0; j < LINES_AMOUNT; j++)
        {
            if (auxLine.Start.x != lines[j].Start.x && auxLine.Start.y != lines[j].Start.y)
            {
                LineIntersections(auxLine.Start.x, auxLine.Start.y, auxLine.Finish.x, auxLine.Finish.y,
                                  lines[j].Start.x, lines[j].Start.y, lines[j].Finish.x, lines[j].Finish.y, lines[j]);
            }
        }
    }
}

void LineIntersections(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3,
                       const float x4, const float y4, Line& line)
{
    // calculate the distance to intersection point
    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
    {
        // optionally, draw a circle where the lines meet
        float intersectionX = x1 + (uA * (x2 - x1));
        float intersectionY = y1 + (uA * (y2 - y1));

        AddCorner(line, intersectionY, intersectionX);

        /*
        DrawCircle(intersectionX, intersectionY, 5, RED);*/
    }
}

void AddCorner(Line& line, const int newY, const int newX)
{
    line.Corners[0].x = newX;
    line.Corners[0].y = newY;
    line.CornersAmount++;
}

bool IsSameCorner(const Vector2& corner1, const Vector2& corner2)
{
    return corner1.x < FLT_EPSILON + corner2.x && corner1.x > corner2.x - FLT_EPSILON
        && corner1.y < FLT_EPSILON + corner2.y && corner1.y > corner2.y - FLT_EPSILON;
}
