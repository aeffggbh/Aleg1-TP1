#pragma once
#include <raylib.h>
#include <vector>

struct Segment
{
	Vector2 start = { 0, 0 };
	Vector2 finish = { 0, 0 };
	std::vector<Vector2> intersections;
	std::vector<int> intersectIndex;
	bool done = false;
	int id;
};

const int START = 1;
const int FINISH = 2;
const int LINES_AMOUNT = 4;

/**
 * @brief saves a coord when left click
 * @return Vector with coordinates
 */
Vector2 GetMouseCoord();

/**
 * @brief Draw a line on screen with color red and save it in an array
 * @param line
 * @param lines
 */
void DrawLine(Segment line);

/// <summary>
/// 
/// </summary>
/// <param name="myLines"> array of lineas </param>
/// <param name="currentPosition"> position of the line being created (START or FINISH) </param>
/// <param name="currentLine"> current position of the line being created</param>
void CheckLinesCreated(Segment myLines[], int& currentPosition, int& currentLine);

void DrawLines(Segment myLines[]);