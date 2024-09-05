#pragma once
#include "Squares.h"

void SearchCorner(Line line[], Line corners[]);
void LineIntersections(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Line intersections[]);
void AddCorner(Line intersections[], int newY, int newX);