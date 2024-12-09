#include "Squares.h"
#include "Geometry.h"
#include <cmath>
#include <list>
#include <iostream>

using namespace Calculations;

/// <summary>
/// Ordeno un array de int de menor a mayor y guardo el resultado en otro array
/// </summary>
/// <param name="original"></param>
/// <param name="result"></param>
static void SortArray(int original[], int result[])
{
	int aux[4];
	for (int i = 0; i < 4; i++)
	{
		aux[i] = original[i];
	}

	for (int i = 0; i < 3; i++)
	{
		int min = i;

		for (int j = i + 1; j < 4; j++)
			if (aux[j] < aux[min])
				min = j;

		std::swap(aux[i], aux[min]);
	}

	for (int i = 0; i < 4; i++)
	{
		result[i] = aux[i];
	}
}

/// <summary>
/// Check if the quad I insert is already in the vector
/// </summary>
/// <param name="quad"></param>
/// <param name="quadList"></param>
/// <returns></returns>
static bool IsQuadInVector(Quad quad, std::vector<Quad> quadList)
{
	for (auto it = quadList.begin(); it != quadList.end(); it++)
	{
		if (IsQuadEqual(*it, quad))
		{
			return true;
		}
	}

	return false;
}


float GetPerimeter(Quad quad, std::vector<Intersection> allIntersections)
{
	return Calculations::CalculatePerimeter(quad, allIntersections);
}

float GetArea(Quad quad, std::vector<Intersection> allIntersections)
{
	return Calculations::CalculateQuadArea(quad, allIntersections);
}

static bool AreDifferentIntersections(Intersection inter1, Intersection inter2) 
{
	return inter1.point.x != inter2.point.x || inter1.point.y != inter2.point.y;
}

static void CalculateQuadAngles(Vector2 quadVertices[4], float angles[4])
{
	// Initialize angles to zero
	for (int i = 0; i < 4; ++i) 
	{
		angles[i] = 0.0f;
	}

	// Calculate angles using the CalculateQuadAngles function
	CalculateQuadAngles(quadVertices, angles, 4);
}

static bool CheckQuadAngleConditions(const float angles[4])
{
	// Check that no angle is 0 or 180 degrees
	//if any of the angles were zero, it would imply that two sides are collinear
	bool isNot0 = !(angles[0] == 0 || angles[1] == 0 || angles[2] == 0 || angles[3] == 0);
	//This would also imply two sides are collinear
	bool isNot180 = !(
		(angles[0] >= 179.0f && angles[0] <= 180.0f) ||
		(angles[1] >= 179.0f && angles[1] <= 180.0f) ||
		(angles[2] >= 179.0f && angles[2] <= 180.0f) ||
		(angles[3] >= 179.0f && angles[3] <= 180.0f)
		);

	return isNot0 && isNot180;
}

static bool AreAnglesValid(Vector2 quadPoints[4])
{
	float angles[4] = { 0 };
	CalculateQuadAngles(quadPoints, angles);

	//Calculate sum of the angles
	float totalAngles = angles[0] + angles[1] + angles[2] + angles[3];
	
	//If the angles sum 360, it's probably a quad. This is because quadrilaterals can be divided in two triangles, triangles angles always sum 180. 180 * 2 = 360
	bool angleConditionsMet = std::abs(totalAngles - 360.0f) < epsilon &&
		CheckQuadAngleConditions(angles);

	return angleConditionsMet;
}

static bool IsAQuad(std::vector<Intersection>& allIntersections, int vertexIndices[4], std::vector<Quad>& quadList)
{
	Vector2 quadPoints[4];
	for (int i = 0; i < 4; ++i) 
		quadPoints[i] = allIntersections[vertexIndices[i]].point;

	// Validate quad angles
	if (!AreAnglesValid(quadPoints))
		return false;

	Quad newQuad;
	// Copy vertex indices
	for (int i = 0; i < 4; ++i) 
		newQuad.verticesIndex[i] = vertexIndices[i];

	// Sort indices
	SortArray(newQuad.verticesIndex, newQuad.sortedVerticesIndex);

	// Add quad if not already in list
	if (!IsQuadInVector(newQuad, quadList))
	{
		quadList.push_back(newQuad);
		return true;
	}

	return false;
}

static void RemoveDuplicateQuads(std::vector<Quad>& quadList)
{
	for (int i = 0; i < quadList.size() - 1; i++) 
		for (int j = i + 1; j < quadList.size(); j++) 
			if (IsQuadEqual(quadList[i], quadList[j])) 
			{
				quadList.erase(quadList.begin() + j);
				j--;
			}
}

void CheckQuads(Segment lines[], std::vector<Quad>& quadList, int intersectionsTotal, std::vector<Intersection>& allIntersections)
{
	//paso por todas las intersecciones que hay
	for (int i = 0; i < intersectionsTotal; i++)
	{
		//guarda una primera interseccion
		Intersection& intersectionA = allIntersections[i];

		//checks both lines that are intersecting (the meaning of 2)
		for (int a = 0; a < 2; a++)
		{
			//guarda el index de una linea, parte de la intersección A
			int lineToCheck = intersectionA.linesIndex[a];

			//cuantas intersecciones tiene esa linea?
			int sizeLineA = lines[lineToCheck].intersectIndex.size();

			//pasa por todas las intersecciones de ella
			for (int j = 0; j < sizeLineA; j++)
			{
				//tomo una de sus intersecciones (el index de ella)
				int interNextA = lines[lineToCheck].intersectIndex[j];

				//chequea que vea la siguiente intersección, no la que ya guarde como A.
				if (AreDifferentIntersections(allIntersections[interNextA], intersectionA))
				{
					//la siguiente a la interseccion A sera la interseccion B.
					Intersection& interB = allIntersections[interNextA];

					//paso por ambas lineas que intersectan a la interseccion b
					for (int b = 0; b < 2; b++)
					{
						//guardo el index de la linea por la que estoy pasando
						int lineIndexB = interB.linesIndex[b];

						int sizeLineB = lines[lineIndexB].intersectIndex.size();

						//paso por todas las intersecciones que tiene la linea B
						for (int k = 0; k < sizeLineB; k++)
						{
							//guardo la siguiente interseccion a B, como hice antes con A
							int interNextB = lines[lineIndexB].intersectIndex[k];

							//chequea que vea la siguiente intersección, no la que ya guarde como B.
							if (AreDifferentIntersections(allIntersections[interNextB], interB) &&
								AreDifferentIntersections(allIntersections[interNextB], intersectionA))
							{
								// la siguiente a la intersección B será la intersección C
								Intersection& interC = allIntersections[interNextB];

								//itero las lineas de la inter C
								for (int c = 0; c < 2; c++)
								{
									//guardo el index de la linea por la que estoy pasando
									int lineIndexC = interC.linesIndex[c];

									//guardo la cantidad de intersecciones que tiene
									int sizeLineC = lines[lineIndexC].intersectIndex.size();

									//paso por ellas
									for (int l = 0; l < sizeLineC; l++)
									{
										//siguiente a C, lo mismo que con las anteriores
										int interNextC = lines[lineIndexC].intersectIndex[l];

										if (AreDifferentIntersections(allIntersections[interNextC], interC) &&
											AreDifferentIntersections(allIntersections[interNextC], interB) &&
											AreDifferentIntersections(allIntersections[interNextC], intersectionA))
										{
											//siguiente interseccion a C sera la D
											Intersection& interD = allIntersections[interNextC];

											//paso por las lineas que pasan por la interseccion
											for (int d = 0; d < 2; d++)
											{
												//las guardo aca 
												int lineIndexD = interD.linesIndex[d];

												//veo cuantas intersecciones tiene
												int sizeLineD = lines[lineIndexD].intersectIndex.size();

												//paso por las intersecciones que tiene la linea
												for (int m = 0; m < sizeLineD; m++)
												{
													//la siguiente linea a D
													int interNextD = lines[lineIndexD].intersectIndex[m];

													if (!AreDifferentIntersections(allIntersections[interNextD], intersectionA) &&
														AreDifferentIntersections(allIntersections[interNextD], interC) &&
														AreDifferentIntersections(allIntersections[interNextD], interB))
													{
														int vertexIndices[4] = 
														{
															interNextA, interNextB,
															interNextC, interNextD
														};

														IsAQuad(allIntersections, vertexIndices, quadList);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (!quadList.empty())  
		RemoveDuplicateQuads(quadList);
}