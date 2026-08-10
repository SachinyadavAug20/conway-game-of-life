#include "simulation.hpp"
#include "ui.hpp"
#include <raylib.h>

const int BOARD_W = 750;
const int BOARD_H = 750;
const int PANEL_W = 400;
const int WINDOW_W = BOARD_W + PANEL_W;
const int WINDOW_H = BOARD_H;
const int MIN_CELL_SIZE = 8;
const int MAX_CELL_SIZE = 75;
const int MIN_FPS = 5;
const int MAX_FPS = 60;
int FPS = 12;
int CELL_SIZE = 25;
int ACTIVE_PRESET = -1;

const int PRESET_KEYS[] = {
    KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_4,
    KEY_KP_5, KEY_KP_6, KEY_KP_7,
    KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN,
};

int main() {
  Color GREY = {29, 29, 29, 255};
  InitWindow(WINDOW_W, WINDOW_H, "Conway's Game of Life");
  Font uiFont = LoadFontEx("assets/fonts/FiraCode-Regular.ttf", 48, 0, 256);
  if (uiFont.texture.id == 0) {
    uiFont = GetFontDefault();
  }
  SetTextureFilter(uiFont.texture, TEXTURE_FILTER_BILINEAR);
  SetTargetFPS(FPS);
  Simulation simulation(BOARD_W, BOARD_H, CELL_SIZE);
  UI ui(uiFont);

  while (WindowShouldClose() == false) {
    // event
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 mousePos = GetMousePosition();
      if (mousePos.x < BOARD_W) {
        int cellSize = simulation.getCellSize();
        int row = mousePos.y / cellSize;
        int col = mousePos.x / cellSize;
        simulation.toggleCell(row, col);
      }
    }

    int presetIndex = -1;
    for (int i = 0; i < 7; i++) {
      if (IsKeyPressed(PRESET_KEYS[i]) || IsKeyPressed(PRESET_KEYS[i + 7])) {
        presetIndex = i;
        break;
      }
    }

    if (presetIndex >= 0) {
      simulation.loadPattern(PRESETS[presetIndex]);
      FPS = PRESETS[presetIndex].fps;
      CELL_SIZE = simulation.getCellSize();
      ACTIVE_PRESET = presetIndex + 1;
      SetTargetFPS(FPS);
    } else if (IsKeyPressed(KEY_SPACE)) {
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
        ACTIVE_PRESET = -1;
        simulation.resize(CELL_SIZE);
      }
    } else if (IsKeyPressed(KEY_LEFT_BRACKET)) {
      if (CELL_SIZE > MIN_CELL_SIZE) {
        CELL_SIZE -= 5;
        ACTIVE_PRESET = -1;
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
    info.activePreset = ACTIVE_PRESET;
    ui.Draw(info);

    EndDrawing();
  }
  UnloadFont(uiFont);
  CloseWindow();
  return 0;
}
