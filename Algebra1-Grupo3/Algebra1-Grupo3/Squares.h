#pragma once
#include "raylib.h"

const int LINES_AMOUNT = 4;

struct Line
{
	Vector2 start;
	Vector2 finish;
};

/**
 * @brief saves a coord when left click
 * @return Vector with coordinates
 */
Vector2 GetMouseCoord();

void MakeLine(Vector2 point1, Vector2 point2, Line lines[LINES_AMOUNT]);

void DetectCorner();