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
    constexpr float step = 0.1f;
    const float mA = FindSlope(lineA);
    const float bA = FindB(lineA, mA);
    const float mB = FindSlope(lineB);
    const float bB = FindB(lineB, mB);
    float yA;
    float yB;

    //traverses the line
    for (float xA = lineA.Start.x; xA <= lineA.Finish.x; xA += step)
    {
        for (float xB = lineB.Start.x; xB <= lineB.Finish.x; xB += step)
        {
            yA = mA * xA + bA;
            yB = xB * mB + bB;
            if (IsSameCorner({xA, yA}, {xB, yB}))
            {
                AddCorner(lineA, yA, xA);
            }
        }
    }
}


void AddCorner(Line& line, const float newY, const float newX)
{
    Vector2 newCorner = {newX, newY};

    if(line.Corners.empty())
    {
        line.Corners.push_back(newCorner);
        return;
    }

    for (auto corner : line.Corners)
        if (!IsSameCorner(corner, newCorner))
        {
            line.Corners.push_back(newCorner);
            return;
        }
}

float FindSlope(const Line& line)
{
    //The rate of change of y depending on x
    return (line.Finish.y - line.Start.y) / (line.Finish.x - line.Start.x);
}

float FindB(const Line& line, const float m)
{
    //The height of the intersections of the lines
    return line.Start.y - m * line.Start.x;
}

bool IsSameCorner(const Vector2& corner1, const Vector2& corner2)
{
    constexpr float margin = 0.5f;
    return corner1.x < margin + corner2.x && corner1.x > corner2.x - margin
        && corner1.y < margin + corner2.y && corner1.y > corner2.y - margin;
}

void DrawCorners(Line line[])
{
    for (int i = 0; i < LINES_AMOUNT; i++)
        for (auto corner : line[i].Corners)
            DrawCircle(corner.x, corner.y, 5, RED);
}
