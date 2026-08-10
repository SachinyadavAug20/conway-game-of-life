#include "ui.hpp"
#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

namespace {
constexpr int PADDING = 14;
constexpr int LINE_HEIGHT = 24;
constexpr int FONT_SIZE = 18;
constexpr int PANEL_X = 762;
constexpr int PANEL_WIDTH = 336;
constexpr Color PANEL_COLOR = {0, 0, 0, 180};
constexpr Color TITLE_COLOR = {255, 255, 255, 255};
constexpr Color TEXT_COLOR = {220, 220, 220, 255};
constexpr Color LABEL_COLOR = {150, 150, 150, 255};
constexpr Color RUN_COLOR = {0, 255, 0, 255};
constexpr Color PAUSE_COLOR = {255, 80, 80, 255};
} // namespace

namespace {
std::string fmt(const char *format, ...) {
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  return std::string(buffer);
}
} // namespace

void UI::Draw(const HudInfo &info) const {
  const float panelX = PANEL_X;
  const float panelY = 12;

  int total = info.live + info.dead;
  int livePct = total > 0 ? (info.live * 100) / total : 0;
  int deadPct = 100 - livePct;

  int statLines = 5;
  int controlLines = 7;
  float panelHeight =
      PADDING * 2 + statLines * LINE_HEIGHT + 24 + (controlLines + 1) * LINE_HEIGHT;

  DrawRectangleRounded({panelX, panelY, PANEL_WIDTH, panelHeight}, 0.12f, 8,
                       PANEL_COLOR);

  float y = panelY + PADDING;
  DrawText("Conway's Game of Life", panelX + PADDING, y, FONT_SIZE,
           TITLE_COLOR);
  y += LINE_HEIGHT;

  drawStatus(info, panelX + PADDING, y, FONT_SIZE);
  y += LINE_HEIGHT;

  DrawText(fmt("FPS: %d / target %d", info.fps, info.targetFps).c_str(),
           panelX + PADDING, y, FONT_SIZE, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawText(fmt("Generation: %d", info.generation).c_str(), panelX + PADDING, y,
           FONT_SIZE, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawText(fmt("Live: %d (%d%%)   Dead: %d (%d%%)", info.live, livePct,
               info.dead, deadPct)
               .c_str(),
           panelX + PADDING, y, FONT_SIZE, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawText(fmt("Grid: %d x %d   Cell: %dpx", info.cols, info.rows,
               info.cellSize)
               .c_str(),
           panelX + PADDING, y, FONT_SIZE, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawLineEx({panelX + PADDING, y + 6},
             {panelX + PANEL_WIDTH - PADDING, y + 6}, 1, LABEL_COLOR);
  y += 24;

  DrawText("Controls", panelX + PADDING, y, FONT_SIZE, LABEL_COLOR);
  y += LINE_HEIGHT;

  const char *controls[] = {
      "SPACE   - pause / resume",
      "LMB     - draw cells",
      "R       - random fill",
      "C       - clear grid",
      "[  /  ] - cell size -/+",
      "W / S   - speed up / down",
      "ESC     - quit",
  };
  for (const char *ctrl : controls) {
    DrawText(ctrl, panelX + PADDING, y, FONT_SIZE, TEXT_COLOR);
    y += LINE_HEIGHT;
  }
}

void UI::drawStatus(const HudInfo &info, float x, float y, float fontSize) const {
  DrawText("Status: ", x, y, fontSize, LABEL_COLOR);
  float width = MeasureText("Status: ", fontSize);
  DrawText(info.running ? "RUNNING" : "PAUSED", x + width, y, fontSize,
           info.running ? RUN_COLOR : PAUSE_COLOR);
}
