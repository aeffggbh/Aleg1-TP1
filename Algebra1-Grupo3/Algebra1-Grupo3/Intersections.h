#pragma once
#include <raylib.h>
#include "Lines.h"

struct Intersection
{
	//donde intersectan?
	Vector2 point = { 0,0 };

	//que lineas intersectan? (guardo los indices de ellas que tendrian en el array de lines)
	int linesIndex[2] = { -1,-1 };
};

void SearchIntersections(Segment line[], int linesCreated, int&, std::vector<Intersection>& allIntersections);
void LineIntersections(Segment& lineA, Segment& lineB, int &currentIntersection, std::vector<Intersection> &allIntersections);
void AddIntersection(Segment& line, float newX, float newY);
void DrawVertices(Segment line[]);

