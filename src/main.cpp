#include <raylib.h>
#include "simulation.hpp"

const int WINDOW_W=750;
const int WINDOW_H=750;
int FPS=12;
int CELL_SIZE=25;
int main(){
  Color GREY={29,29,29,255};
  InitWindow(WINDOW_W, WINDOW_H, "Conway's Game of Life");
  SetTargetFPS(FPS);
  Simulation simulation(WINDOW_W, WINDOW_H, CELL_SIZE);

  while (WindowShouldClose()==false) {
    BeginDrawing();
    ClearBackground(GREY);
    simulation.Draw();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
