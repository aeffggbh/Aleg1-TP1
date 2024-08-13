#include <iostream>
#include "Squares.h"

using namespace std;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    //vector de prueba
    Vector2 vectorTest;
    
    InitWindow(screenWidth, screenHeight, "Raylib basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("It works!", 20, 20, 20, BLACK);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            vectorTest = GetMouseCoord();
        }
        
    }
    CloseWindow();
    return 0;
}

