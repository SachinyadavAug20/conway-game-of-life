#include "simulation.hpp"
#include <raylib.h>

const int WINDOW_W = 750;
const int WINDOW_H = 750;
int FPS = 12;
int CELL_SIZE = 25;
int main() {
  Color GREY = {29, 29, 29, 255};
  InitWindow(WINDOW_W, WINDOW_H, "Conway's Game of Life");
  SetTargetFPS(FPS);
  Simulation simulation(WINDOW_W, WINDOW_H, CELL_SIZE);

  while (WindowShouldClose() == false) {
    // event
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
      Vector2 mousePos = GetMousePosition();
      int row=mousePos.y/CELL_SIZE;
      int col=mousePos.x/CELL_SIZE;
      simulation.ToggleCell(row, col);
    }

    if (IsKeyPressed(KEY_SPACE)) {
      simulation.stop();
      SetWindowTitle("Game of Life is stoped...");
    } else if (IsKeyPressed(KEY_ENTER)) {
      simulation.start();
      SetWindowTitle("Game of Life is running...");
    } else if (IsKeyPressed(KEY_UP) ||
               (IsKeyPressed(KEY_F) || IsKeyPressed(KEY_W))) {
      if(FPS<60) FPS+=2, SetTargetFPS(FPS);
    } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
      if(FPS>5) FPS-=2, SetTargetFPS(FPS);
    } else if (IsKeyPressed(KEY_R)) simulation.CreateRandomState();
    else if (IsKeyPressed(KEY_C)) simulation.ClearGride();

    // update
    simulation.update();

    // draw
    BeginDrawing();
    ClearBackground(GREY);
    simulation.Draw();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
