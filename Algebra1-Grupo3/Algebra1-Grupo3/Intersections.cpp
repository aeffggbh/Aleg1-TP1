#include "Intersections.h"
#include <iostream>
#include <vector>

//3

/// <summary>
/// Se buscan las intersecciones que se hicieron
/// </summary>
/// <param name="line"></param>
/// <param name="linesCreated"></param>
/// <param name="intersectionsTotal"></param>
/// <param name="allIntersections"></param>
void SearchIntersections(Segment line[], const int linesCreated, int& intersectionsTotal, std::vector<Intersection>& allIntersections)
{
	//define ids

	for (int i = 0; i < linesCreated; i++)
	{
		if (line[i].id != i)
		{
			line[i].id = i;
		}
	}

	//chequea intersecciones
	for (int i = 0; i < linesCreated; i++)
		for (int j = i + 1; j < linesCreated; j++)
			LineIntersections(line[i], line[j], intersectionsTotal, allIntersections);
}

static bool VectorEquals(Vector2 a, Vector2 b)
{
	return a.x == b.x && a.y == b.y;
}

static bool IsIntersectionInLine(Segment line, Vector2 intersection)
{
	for (int i = 0; i < line.intersections.size(); i++)
	{
		if (VectorEquals(line.intersections[i], intersection))
		{
			return true;
		}
	}

	return false;
}

//https://www.jeffreythompson.org/collision-detection/line-line.php
void LineIntersections(Segment& lineA, Segment& lineB, int& currentIntersection, std::vector<Intersection>& allIntersections)
{
	// Calculate the distances from the start of lineA to the intersection point
	float distanceToIntersection =
			((lineB.finish.x - lineB.start.x) *
			(lineA.start.y - lineB.start.y) - (lineB.finish.y - lineB.start.y) *
			(lineA.start.x - lineB.start.x)) 
		/ ((lineB.finish.y - lineB.start.y) *
		  (lineA.finish.x - lineA.start.x) - (lineB.finish.x - lineB.start.x) *
		  (lineA.finish.y - lineA.start.y));

	if (distanceToIntersection >= 0 && distanceToIntersection <= 1)
	{
		float intersectionX = lineA.start.x + (distanceToIntersection * (lineA.finish.x - lineA.start.x));
		float intersectionY = lineA.start.y + (distanceToIntersection * (lineA.finish.y - lineA.start.y));

		Vector2 intersection = { intersectionX, intersectionY };

		if (!IsIntersectionInLine(lineA, intersection) && !IsIntersectionInLine(lineB, intersection))
		{
			AddIntersection(lineA, intersectionX, intersectionY);
			AddIntersection(lineB, intersectionX, intersectionY);

			Intersection aux;
			aux.linesIndex[0] = lineA.id;
			aux.linesIndex[1] = lineB.id;
			aux.point = intersection;

			allIntersections.push_back(aux);

			lineA.intersectIndex.push_back(currentIntersection);
			lineB.intersectIndex.push_back(currentIntersection);

			currentIntersection++;
		}
	}
	else
		return;

}

static bool IsSameIntersection(const Vector2& vertex1, const Vector2& vertex2, const float margin)
{
	//these are useful for readability
	bool cond1 = false;
	bool cond2 = false;
	//se fija si son iguales tomando en cuenta un margen
	if (vertex1.x < margin + vertex2.x && vertex1.x > vertex2.x - margin)
		cond1 = true;

	if (vertex1.y < margin + vertex2.y && vertex1.y > vertex2.y - margin)
		cond2 = true;

	return cond1 && cond2;
}

void AddIntersection(Segment& line, const float newX, const float newY)
{
	Vector2 newIntersection = { newX, newY };

	if (line.intersections.empty())
	{
		line.intersections.push_back(newIntersection);
		return;
	}

	for (auto vertex : line.intersections)
		//se fija que esa linea no tenga una intersección ya
		if (!IsSameIntersection(vertex, newIntersection, 3))
		{
			line.intersections.push_back(newIntersection);
			return;
		}
}


void DrawVertices(Segment line[])
{
	for (int i = 0; i < LINES_AMOUNT; i++)
	{
		if (line[i].done)
			for (auto vertex : line[i].intersections)
				DrawCircle(vertex.x, vertex.y, 5, RED);
	}
}
