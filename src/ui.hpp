#pragma once
#include <raylib.h>

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
};

class UI {
public:
  void Draw(const HudInfo &info) const;

private:
  void drawStatus(const HudInfo &info, float x, float y, float fontSize) const;
};
