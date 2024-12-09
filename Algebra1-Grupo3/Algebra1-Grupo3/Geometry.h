#pragma once
#include "Squares.h"
#include <iostream>
#include "raylib.h"

namespace Calculations
{
	const double epsilon = 1E-05;

	double GetAreaOfATriangle(double a, double b, double c);

	bool ArePointsCollinear(Vector2 a, Vector2 b, Vector2 c);

	double GetDotProduct(Vector2 a, Vector2 b);

	double GetMagnitude(Vector2 v);

	double GetCrossProduct(Vector2 a, Vector2 b);

	double GetAngle(Vector2 a, Vector2 b);

	float Distance(Vector2 a, Vector2 b);

	float CalculatePerimeter(Quad quad, std::vector<Intersection> allIntersections);

	double GetArea(Vector2 A, Vector2 B, Vector2 C, Vector2 D);

	float CalculateQuadArea(Quad quad, std::vector<Intersection> allIntersections);

	// Suma todos los angulos
	void CalculateQuadAngles(Vector2 points[], float angles[], int count);

	bool IsQuadEqual(Quad q1, Quad q2);
}
