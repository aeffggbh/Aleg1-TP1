#include <iostream>
#include "Squares.h"

using namespace std;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    int currentLine = 0;

    //vector de prueba
    Vector2 vectorTest;
    
    InitWindow(screenWidth, screenHeight, "Quad test");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            vectorTest = GetMouseCoord();
        }
        
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("Clic on two positions!", 20, 20, 20, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

