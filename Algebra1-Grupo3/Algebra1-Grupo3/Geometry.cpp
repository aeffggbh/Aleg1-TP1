#include "Geometry.h"

//4

namespace Calculations
{
	/// <summary>
	/// Heron's formula
	/// I calculate the area of a triangle given its sides.
	/// It's a formula that works for any triangle.
	/// https://www.geogebra.org/m/K42Xma77#:~:text=Se%20expresa%20normalmente%20en%20funci%C3%B3n,haciendo%20que%20sea%20d%20%3D%200.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="c"></param>
	/// <returns></returns>
	double GetAreaOfATriangle(double sideA, double sideB, double sideC)
	{
		//s
		double semiPerimeter = (sideA + sideB + sideC) / 2;

		return sqrt(semiPerimeter * (semiPerimeter - sideA) * (semiPerimeter - sideB) * (semiPerimeter - sideC));
	}

	/// <summary>
	/// Si los vectores apuntan en la misma dirección → cos(θ) = 1
	/// Si son perpendiculares → cos(θ) = 0
	///	Si apuntan en direcciones opuestas → cos(θ) = -1
	/// https://es.khanacademy.org/math/multivariable-calculus/thinking-about-multivariable-function/x786f2022:vectors-and-matrices/a/dot-products-mvc
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	double GetDotProduct(Vector2 a, Vector2 b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	/// <summary>
	/// Pitagoras
	/// component in X: base (a)
	/// component in Y: height (b)
	/// magnitude: hypotenuse (c)
	/// c = √(a² + b²)
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	double GetMagnitude(Vector2 v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	/// <summary>
	/// Saca un vector perpendicular a otros dos
	/// https://es.khanacademy.org/math/multivariable-calculus/thinking-about-multivariable-function/x786f2022:vectors-and-matrices/a/cross-products-mvc
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	double GetCrossProduct(Vector2 a, Vector2 b)
	{
		return (a.x * b.y) - (a.y * b.x);
	}

	/// <summary>
	/// Saca el angulo entre dos vectores basandose en la formula del producto punto.
	/// Primero calcula el angulo mas chico, luego verifica si es el angulo correcto o si es mayor a 
	/// 180 grados dependiendo su direccion
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	double GetAngle(Vector2 a, Vector2 b)
	{
		double dotProduct = GetDotProduct(a, b);
		double magnitudeA = GetMagnitude(a);
		double magnitudeB = GetMagnitude(b);

		//get the cosine of the angle
		//dotProduct = (magnitudeA * magnitudeB) * cosTheta;
		double cosTheta = dotProduct / (magnitudeA * magnitudeB);

		//cosTheta will always be a number between -1 and 1, but I do this only to prevent wrong calculations
		if (cosTheta > 1.0)
			cosTheta = 1.0;
		if (cosTheta < -1.0)
			cosTheta = -1.0;

		//calcula el menor angulo entre los vectores (entre 0 y PI o 0 y 180 cuando se pasa a grados)
		double radiansAngle = acos(cosTheta);
		double degreesAngle = radiansAngle * (180.0 / PI);

		/*
			indica si el vector b está a la izquierda o a la derecha de a en el plano 2D.
			Si crossProduct > 0, b está a la izquierda de a
			Si crossProduct < 0, b está a la derecha de a
			Si crossProduct == 0, los vectores son colineales.
		*/
		double crossProduct = GetCrossProduct(a, b);

		//si crossproduct < 0 esta a la derecha de a, lo que quiere decir que el angulo es mayor a 180 grados (Concavo)
		if (crossProduct < 0)
		{
			degreesAngle = 360.0 - degreesAngle;
		}

		//
		//		|
		//		|
		//	____|
		// 
		// No va a ser el mismo algulo que
		//
		//
		//		|
		//		|
		//		|____
		// 
		// Pero si solo hacemos el primer calculo, si lo va a ser.

		return degreesAngle;
	}

	/// <summary>
	/// Pitagoras
	/// Se saca la distancia entre un punto y otro
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	float Distance(Vector2 a, Vector2 b)
	{
		//Pitagoras
		return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	}

	/// <summary>
	/// Suma de los lados
	/// Los lados serán la distancia entre cada uno de los puntos del cuadrilateros.
	/// </summary>
	/// <param name="quad"></param>
	/// <param name="allIntersections"></param>
	/// <returns></returns>
	float CalculatePerimeter(Quad quad, std::vector<Intersection> allIntersections)
	{
		Vector2 points[4];

		for (int j = 0; j < 4; j++)
		{
			points[j] = allIntersections[quad.verticesIndex[j]].point;
		}

		double distanceA = Distance(points[0], points[1]);
		double distanceB = Distance(points[1], points[2]);
		double distanceC = Distance(points[2], points[3]);
		double distanceD = Distance(points[3], points[0]);

		return distanceA + distanceB + distanceC + distanceD;
	}

	/// <summary>
	/// Se divide el cuadrilatero en dos triangulos, se calcula el area de ellos y se hace la suma de estas.
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <param name="C"></param>
	/// <param name="D"></param>
	/// <returns></returns>
	double GetArea(Vector2 A, Vector2 B, Vector2 C, Vector2 D)
	{
		double area1 = GetAreaOfATriangle(Distance(A, B), Distance(B, D), Distance(D, A));
		double area2 = GetAreaOfATriangle(Distance(B, C), Distance(C, D), Distance(B, D));

		return area1 + area2;
	}

	/// <summary>
	/// Función para falicitar el calculo del area (solo le inserto el cuadrilatero y las intersecciones)
	/// </summary>
	/// <param name="quad"></param>
	/// <param name="allIntersections"></param>
	/// <returns></returns>
	float CalculateQuadArea(Quad quad, std::vector<Intersection> allIntersections)
	{
		return GetArea(allIntersections[quad.verticesIndex[0]].point, allIntersections[quad.verticesIndex[1]].point,
			allIntersections[quad.verticesIndex[2]].point, allIntersections[quad.verticesIndex[3]].point);
	}

	void CalculateQuadAngles(Vector2 vertices[], float angles[], int anglesAmount)
	{
		for (int i = 0; i < anglesAmount; i++)
		{
			//crea un vector entre un vertice y otro
			//cuando i + 1 == 4 entonces vuelve a la posicion 0
			Vector2 v1 = { vertices[i].x - vertices[(i + 1) % anglesAmount].x,
							vertices[i].y - vertices[(i + 1) % anglesAmount].y };

			Vector2 v2 = { vertices[(i + 2) % anglesAmount].x - vertices[(i + 1) % anglesAmount].x,
							vertices[(i + 2) % anglesAmount].y - vertices[(i + 1) % anglesAmount].y };

			//calcula el angulo entre ellos
			float angle = GetAngle(v1, v2);
			//guarda ese angulo en el array de angulos
			angles[i] = angle;
		}
	}

	/// <summary>
	/// Compares the sorted vertices of both quadrilaterals to see if I'm checking the same one
	/// </summary>
	/// <param name="q1"></param>
	/// <param name="q2"></param>
	/// <returns></returns>
	bool IsQuadEqual(Quad q1, Quad q2)
	{
		int count = 0;

		for (int i = 0; i < 4; i++)
		{
			if (q1.sortedVerticesIndex[i] == q2.sortedVerticesIndex[i])
				count++;
		}

		return count >= 4;
	}
}