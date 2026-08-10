#include "simulation.hpp"
#include "ui.hpp"
#include <raylib.h>

const int BOARD_W = 750;
const int BOARD_H = 750;
const int PANEL_W = 360;
const int WINDOW_W = BOARD_W + PANEL_W;
const int WINDOW_H = BOARD_H;
const int MIN_CELL_SIZE = 8;
const int MAX_CELL_SIZE = 75;
const int MIN_FPS = 5;
const int MAX_FPS = 60;
int FPS = 12;
int CELL_SIZE = 25;

int main() {
  Color GREY = {29, 29, 29, 255};
  InitWindow(WINDOW_W, WINDOW_H, "Conway's Game of Life");
  SetTargetFPS(FPS);
  Simulation simulation(BOARD_W, BOARD_H, CELL_SIZE);
  UI ui;

  while (WindowShouldClose() == false) {
    // event
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 mousePos = GetMousePosition();
      if (mousePos.x < BOARD_W) {
        int row = mousePos.y / CELL_SIZE;
        int col = mousePos.x / CELL_SIZE;
        simulation.toggleCell(row, col);
      }
    }

    if (IsKeyPressed(KEY_SPACE)) {
      simulation.toggleRunning();
    } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
      if (FPS < MAX_FPS) {
        FPS += 2;
        SetTargetFPS(FPS);
      }
    } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
      if (FPS > MIN_FPS) {
        FPS -= 2;
        SetTargetFPS(FPS);
      }
    } else if (IsKeyPressed(KEY_R)) {
      simulation.createRandomState();
    } else if (IsKeyPressed(KEY_C)) {
      simulation.ClearGrid();
    } else if (IsKeyPressed(KEY_RIGHT_BRACKET)) {
      if (CELL_SIZE < MAX_CELL_SIZE) {
        CELL_SIZE += 5;
        simulation.resize(CELL_SIZE);
      }
    } else if (IsKeyPressed(KEY_LEFT_BRACKET)) {
      if (CELL_SIZE > MIN_CELL_SIZE) {
        CELL_SIZE -= 5;
        simulation.resize(CELL_SIZE);
      }
    }

    // update
    simulation.update();

    // draw
    BeginDrawing();
    ClearBackground(GREY);
    simulation.Draw();

    HudInfo info;
    info.running = simulation.IsRunning();
    info.fps = GetFPS();
    info.targetFps = FPS;
    info.generation = simulation.getGeneration();
    info.live = simulation.getLiveCount();
    info.dead = simulation.getDeadCount();
    info.rows = simulation.getRows();
    info.cols = simulation.getCols();
    info.cellSize = simulation.getCellSize();
    ui.Draw(info);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
