#include "Lines.h"

//devuelve las coordenadas del mouse
Vector2 GetMouseCoord()
{
	Vector2 vector;

	vector.x = GetMouseX();
	vector.y = GetMouseY();

	return vector;
}

//dibuja la linea, con un paso innecesario xd
void DrawLine(Segment line)
{
	DrawLine(line.start.x, line.start.y, line.finish.x, line.finish.y, RED);

}

void CheckLinesCreated(Segment myLines[], int& currentPosition, int& currentLine)
{
	Vector2 mousePos;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		mousePos = GetMouseCoord();

		if (!myLines[currentLine].done && currentLine < LINES_AMOUNT)
		{
			//las lineas empiezan teniendo una posicion inicial, por lo que primero entran aca
			if (currentPosition == START)
			{
				myLines[currentLine].start.x = mousePos.x;
				myLines[currentLine].start.y = mousePos.y;
				//ya se empezo a crear esta linea, por lo que lo siguiente seria terminarla
				currentPosition = FINISH;
			}
			else
			{
				myLines[currentLine].finish.x = mousePos.x;
				myLines[currentLine].finish.y = mousePos.y;
				//ya se termino esta linea, por lo que la siguiente linea se creará desde la posicion inicial
				currentPosition = START;
				//la linea en la que estoy ya está terminada
				myLines[currentLine].done = true;
				//itero a la siguiente linea
				currentLine++;
			}
		}
	}
}

//se dibujan todas las lineas
void DrawLines(Segment myLines[])
{
	for (int i = 0; i < LINES_AMOUNT; i++)
	{
		if (myLines[i].done)
		{
			DrawLine(myLines[i]);
		}
	}
}