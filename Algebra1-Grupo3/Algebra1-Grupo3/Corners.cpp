#include "Corners.h"
bool IsNearCorner(const Vector2& corner1, const Vector2& corner2);

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
    const float startA = lineA.Start.x < lineA.Finish.x ? lineA.Start.x : lineA.Finish.x;
    const float finishA = lineA.Start.x > lineA.Finish.x ? lineA.Start.x : lineA.Finish.x;
    const float startB = lineB.Start.x < lineB.Finish.x ? lineB.Start.x : lineB.Finish.x;
    const float finishB = lineB.Start.x > lineB.Finish.x ? lineB.Start.x : lineB.Finish.x;

    for (float xA = startA ; xA <= finishA; xA += step)
    {
        for (float xB = startB; xB <= finishB; xB += step)
        {
            bool isAlone = true;
            yA = mA * xA + bA;
            yB = xB * mB + bB;
            for(auto corner : lineA.Corners)
            {
                if(IsNearCorner({xA, yA}, corner))
                {
                    isAlone = false;
                    break;
                }

            }
            if (IsSameCorner({xA, yA}, {xB, yB}) && isAlone)
            {
                AddCorner(lineA, xA, yA);
            }
        }
    }
}


void AddCorner(Line& line, const float newX, const float newY)
{
    Vector2 newCorner = {newX, newY};

    if (line.Corners.empty())
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
    constexpr float margin = 1;
    return corner1.x < margin + corner2.x && corner1.x > corner2.x - margin
        && corner1.y < margin + corner2.y && corner1.y > corner2.y - margin;
}

void DrawCorners(Line line[])
{
    for (int i = 0; i < LINES_AMOUNT; i++)
        for (auto corner : line[i].Corners)
            DrawCircle(corner.x, corner.y, 5, RED);
}
bool IsNearCorner(const Vector2& corner1, const Vector2& corner2)
{
    return 1 > (corner2.x - corner1.x) * (corner2.x - corner1.x) + (corner2.y - corner1.y) * (corner2.y - corner1.y);
}
