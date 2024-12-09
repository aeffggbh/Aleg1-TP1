#include "Application.h"
#include <iostream>
#include "Squares.h"
#include "Geometry.h"

//1

using namespace std;

bool quadDone;

void MainLoop()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	int currentLine = 0; //sirve como iterador para las lineas
	int currentPosition = START;
	Segment lines[LINES_AMOUNT];	//las lineas que tiene cada cuadrado
	std::vector<Quad> quadVector; //guarda los cuadris que se van haciendo
	bool quadLooked = false;
	bool reset = false;

	int intersectionsTotal = 0;

	std::vector<Intersection> allIntersections;
	

	InitWindow(screenWidth, screenHeight, "Quad test");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		if (reset)
		{
			quadVector.clear();
			allIntersections.clear();
			intersectionsTotal = 0;
			quadLooked = false;
			currentPosition = START;
			currentLine = 0;

			for (int i = 0; i < LINES_AMOUNT; i++)
			{
				lines[i].done = false;
				lines[i].intersectIndex.clear();
				lines[i].intersections.clear();
			}

			reset = false;
		}

		//si aún no hay un cuadrilatero, se chequean las lineas que se van creando
		if (currentLine < LINES_AMOUNT)
		{
			CheckLinesCreated(lines, currentPosition, currentLine);

			SearchIntersections(lines, currentLine, intersectionsTotal, allIntersections);
		}
		//cuando se terminan de crear las lineas, empieza a buscar los cuadrilateros.
		else if (!quadLooked)
		{
			CheckQuads(lines, quadVector, intersectionsTotal, allIntersections);
			quadLooked = true;
		}
		if (quadLooked)
		{
			std::cout << "quads amount:" << quadVector.size() << std::endl;
			for (int i = 0; i < quadVector.size(); i++)
			{
				std::cout << "Quad ID: " << i << std::endl;
				std::cout << "perimeter: " << GetPerimeter(quadVector[i], allIntersections) << std::endl;
				std::cout << "area: " << GetArea(quadVector[i], allIntersections) << std::endl;
			}

			if (IsKeyReleased(KEY_SPACE))
			{
				reset = true;
			}
		}

		
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Clic on two positions!", 20, 20, 20, WHITE);

		DrawLines(lines);

		DrawVertices(lines);

		EndDrawing();
	}

	CloseWindow();
}