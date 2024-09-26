#pragma once
#include "Squares.h"

void SearchCorner(Line line[]);
void LineIntersections(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Vector2 Corners[]);
void AddCorner(Vector2 Corners[], int newY, int newX);