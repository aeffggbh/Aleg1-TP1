#include "Corners.h"

void SearchCorner(Line line[], const int linesCreated)
{
    for (int i = 0; i < linesCreated; i++)
        for (int j = i + 1; j < linesCreated; j++)
               LineIntersections(line[i], line[j]);
}

void LineIntersections(Line& lineA, const Line& lineB)
{
    // y = m x + B

    const float step = 0.01f;

    const float mA = FindM(lineA);
    const float bA = FindB(lineA, mA);
    const float mB = FindM(lineB);
    const float bB = FindB(lineB, mB);

    //traverses the line
    for (float xA = lineA.Start.x; xA <= lineA.Finish.x; xA += step)
    {
        for (float xB = lineB.Start.x; xB <= lineB.Finish.x; xB += step)
        {
            if ((mA * xA + bA - bB) / mB == xB)
            {
                const float yA = mA * xA + bA;
                AddCorner(lineA, yA, xA);
            }
        }
    }
}


void AddCorner(Line& line, const float newY, const float newX)
{
    Vector2 newCorner = {newX, newY};

    for (int i = 0; i < MAX_CORNERS; i++)
        if (!IsSameCorner(line.Corners[i], newCorner))
        {
            line.Corners[i] = newCorner;
            line.CornersAmount++;
            return;
        }
}

float FindM(const Line& line)
{
    //The rate of change of y depending on x
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

void DrawCorners(Line line[])
{
    for (int i = 0; i < LINES_AMOUNT; i++)
        for (int j = 0; j < MAX_CORNERS; j++)
            DrawCircle(line[i].Corners[j].x, line[i].Corners[j].y, 5, RED);
}
