#pragma once
#include <raylib.h>
#include <vector>
#include "Intersections.h"

struct Quad
{
	//saves unordered vertices
	int verticesIndex[4];
	//prevent multiple checks because of order of vertices inserted (ABCD, DCBA, etc)
	int sortedVerticesIndex[4];
};

float GetPerimeter(Quad quad, std::vector<Intersection> allIntersections);

float GetArea(Quad quad, std::vector<Intersection> allIntersections);

void CheckQuads(Segment lines[], std::vector<Quad>& quadList, int intersectionsTotal, std::vector<Intersection>& allIntersections);

bool IsSameVertex(const Vector2& vertex1, const Vector2& vertex2, float margin = 1);
