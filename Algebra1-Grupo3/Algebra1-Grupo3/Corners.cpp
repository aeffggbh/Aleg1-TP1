#include "Corners.h"

void SearchCorner(Line line[])
{
    for (int i = 0; i < LINES_AMOUNT; i++)
        for (int j = i + 1; j < LINES_AMOUNT; j++)
               LineIntersections(lines[i], lines[j]);
}

void LineIntersections(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Vector2 Corners[])
{
    // y = m x + B

    const float step = 0.05f;

    const float m_A = FindM(line_A);
    float b_A = FindB(line_A, m_A);
    const float m_B = FindM(line_B);
    float b_B = FindB(line_B, m_B);

    //traverses the line
    for (float x = line_A.Start.x; x < line_A.Finish.x; x += step)
    {
        for (float y = line_B.Start.y; y < line_B.Finish.y; y += step)
        {
            if ((m_A * x + b_A - b_B) / m_B == y)
            {
                AddCorner(line_A, x, y);
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
