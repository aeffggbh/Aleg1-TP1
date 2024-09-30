#pragma once
#include <raylib.h>
#include <vector>
#include "Lines.h"



struct Quad
{
	Vector2 C1;
	Vector2 C2;
	Vector2 C3;
	Vector2 C4;
};

/**
 * @brief Detects if it is a Quad and if it is, it appends to quadList
 * @param lines array with lines
 * @param firstCorner start of possible quad
 * @param thisCorner which corner is currently at
 * @param quadCorners array with possible corners
 * @param segments int with the amount of segments that have been found
 * @param quadList vector with quads
 * @return whether a quad was found or not
 */
bool IsAQuad(Line lines[], Vector2 firstCorner, Vector2 thisCorner, Vector2 quadCorners[4], int segments,
             std::vector<Quad>
             quadList);

/**
 * @brief checks whether 2 quads are the same quad
 * @param quad1 first quad to compare
 * @param quad2 second quad to compare
 * @return whether is same quad or not
 */
bool IsSameQuad(Vector2 quad1[], Quad& quad2);

/**
 * @brief check whether two corners are the same or nor
 * @param corner1 first corner to compare
 * @param corner2 second corner to compare
 * @return whether is same cornet or not
 */
bool IsSameCorner(const Vector2& corner1, const Vector2& corner2);

float Distance(Vector2 a, Vector2 b);

float CalculatePerimeter(Quad quad);

float CalculateQuadArea(Quad quad);