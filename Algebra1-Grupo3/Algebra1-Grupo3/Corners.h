#pragma once
#include "Squares.h"

void SearchCorner(Line line[]);
void LineIntersections(Line& line_A, Line& line_B);
void AddCorner(Line& line, float newY, float newX);
float FindM(const Line& line);
float FindB(const Line& line, float m);
void DrawCorners(Line line[]);

