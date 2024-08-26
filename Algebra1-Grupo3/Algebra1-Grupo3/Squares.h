#pragma once
#include <raylib.h>
#include <vector>

const int LINES_AMOUNT = 4;
const int START = 1;
const int FINISH = 2;

struct Line
{
	Vector2 Start;
	Vector2 Finish;
	Vector2 Corners[4];
	int CornersAmount;
	bool Done = false;
};

struct Quad
{
	Vector2 C1;
	Vector2 C2;
	Vector2 C3;
	Vector2 C4;
};

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
void DrawLine(Line line, Line lines[LINES_AMOUNT], int currentPos);

/**
 * @brief 
 * @param lines 
 * @param firstCorner 
 * @param thisCorner 
 * @param quadCorners 
 * @param segments 
 * @param QuadList 
 * @return 
 */
bool IsAQuad(Line lines[], Vector2 firstCorner, Vector2 thisCorner, Vector2 quadCorners[4], int segments,
             std::vector<Quad>
             QuadList);

/**
 * @brief
 * @param quadCorners 
 * @param QuadList 
 * @param quad 
 * @return 
 */
bool IsSameQuad(Vector2* quadCorners, std::vector<Quad> QuadList, int quad);

bool IsSameCorner(const Vector2& corner1, const Vector2& corner2);
