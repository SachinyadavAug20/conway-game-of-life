#include <raylib.h>

const int WINDOW_W=750;
const int WINDOW_H=750;
int FPS=12;
int main(){
  InitWindow(WINDOW_W, WINDOW_H, "Conway's Game of Life");
  SetTargetFPS(FPS);
  while (WindowShouldClose()==false) {
    BeginDrawing();
    ClearBackground(DARKGRAY);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
