#pragma once
#include <raylib.h>

constexpr Color UI_KEY_BG = {235, 235, 235, 255};

struct HudInfo {
  bool running;
  int fps;
  int targetFps;
  int generation;
  int live;
  int dead;
  int rows;
  int cols;
  int cellSize;
  int activePreset;
};

class UI {
public:
  UI(Font font) : font(font) {}
  void Draw(const HudInfo &info) const;

private:
  float drawKeycap(const char *key, float x, float y,
                   Color bg = UI_KEY_BG) const;
  void drawStatus(const HudInfo &info, float x, float y) const;

  Font font;
};
