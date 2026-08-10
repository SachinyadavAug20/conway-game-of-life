#include "ui.hpp"
#include "patterns.hpp"
#include <cstdarg>
#include <cstdio>
#include <string>

namespace {
constexpr int PADDING = 14;
constexpr int LINE_HEIGHT = 27;
constexpr int TITLE_SIZE = 24;
constexpr int FONT_SIZE = 20;
constexpr float SPACING = 1.0f;
constexpr int PANEL_X = 762;
constexpr int PANEL_WIDTH = 376;
constexpr Color PANEL_COLOR = {0, 0, 0, 180};
constexpr Color TITLE_COLOR = {255, 255, 255, 255};
constexpr Color TEXT_COLOR = {220, 220, 220, 255};
constexpr Color LABEL_COLOR = {150, 150, 150, 255};
constexpr Color RUN_COLOR = {0, 255, 0, 255};
constexpr Color PAUSE_COLOR = {255, 80, 80, 255};
constexpr Color KEY_FG = {25, 25, 25, 255};
constexpr int KEY_PAD = 8;
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

  int statLines = 6;
  int presetLines = 8;
  int controlLines = 9;
  float panelHeight = PADDING * 2 + (statLines + presetLines + controlLines) *
                                         LINE_HEIGHT +
                      24 + 24;

  DrawRectangleRounded({panelX, panelY, PANEL_WIDTH, panelHeight}, 0.12f, 8,
                       PANEL_COLOR);

  float y = panelY + PADDING;
  DrawTextEx(font, "Conway's Game of Life", {panelX + PADDING, y}, TITLE_SIZE,
             SPACING, TITLE_COLOR);
  y += LINE_HEIGHT + 2;

  drawStatus(info, panelX + PADDING, y);
  y += LINE_HEIGHT;

  DrawTextEx(font, fmt("FPS: %d / target %d", info.fps, info.targetFps).c_str(),
             {panelX + PADDING, y}, FONT_SIZE, SPACING, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawTextEx(font, fmt("Generation: %d", info.generation).c_str(),
             {panelX + PADDING, y}, FONT_SIZE, SPACING, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawTextEx(font, fmt("Live: %d (%d%%)   Dead: %d (%d%%)", info.live, livePct,
                       info.dead, deadPct)
                       .c_str(),
             {panelX + PADDING, y}, FONT_SIZE, SPACING, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawTextEx(font, fmt("Grid: %d x %d   Cell: %dpx", info.cols, info.rows,
                       info.cellSize)
                       .c_str(),
             {panelX + PADDING, y}, FONT_SIZE, SPACING, TEXT_COLOR);
  y += LINE_HEIGHT;

  DrawLineEx({panelX + PADDING, y + 6},
             {panelX + PANEL_WIDTH - PADDING, y + 6}, 1, LABEL_COLOR);
  y += 24;

  DrawTextEx(font, "Presets", {panelX + PADDING, y}, FONT_SIZE, SPACING,
             LABEL_COLOR);
  float nextX = panelX + PADDING + MeasureTextEx(font, "Presets", FONT_SIZE,
                                                 SPACING)
                                  .x +
                12;
  drawKeycap("1-7", nextX, y);
  y += LINE_HEIGHT;

  for (int i = 0; i < 7; i++) {
    bool active = (i + 1) == info.activePreset;
    drawKeycap(fmt("%d", i + 1).c_str(), panelX + PADDING, y,
               active ? RUN_COLOR : UI_KEY_BG);
    float nameX = panelX + PADDING + 40;
    DrawTextEx(font, PRESETS[i].name, {nameX, y + 2}, FONT_SIZE, SPACING,
               active ? RUN_COLOR : TEXT_COLOR);
    y += LINE_HEIGHT;
  }

  DrawLineEx({panelX + PADDING, y + 6},
             {panelX + PANEL_WIDTH - PADDING, y + 6}, 1, LABEL_COLOR);
  y += 24;

  DrawTextEx(font, "Controls", {panelX + PADDING, y}, FONT_SIZE, SPACING,
             LABEL_COLOR);
  y += LINE_HEIGHT;

  struct Control {
    const char *key;
    const char *action;
  };
  const Control controls[] = {
      {"SPACE", "pause / resume"},
      {"LMB", "draw cells"},
      {"R", "random fill"},
      {"C", "clear grid"},
      {"[ ]", "cell size -/+"},
      {"1-7", "load preset"},
      {"W/S", "speed up / down"},
      {"ESC", "quit"},
  };
  for (const Control &ctrl : controls) {
    float x = drawKeycap(ctrl.key, panelX + PADDING, y);
    DrawTextEx(font, ctrl.action, {x + 10, y + 2}, FONT_SIZE, SPACING,
               TEXT_COLOR);
    y += LINE_HEIGHT;
  }
}

float UI::drawKeycap(const char *key, float x, float y, Color bg) const {
  Vector2 size = MeasureTextEx(font, key, FONT_SIZE, SPACING);
  float capW = size.x + KEY_PAD * 2;
  float capH = LINE_HEIGHT - 4;
  DrawRectangleRounded({x, y + 2, capW, capH}, 0.25f, 6, bg);
  DrawTextEx(font, key, {x + KEY_PAD, y}, FONT_SIZE, SPACING, KEY_FG);
  return x + capW;
}

void UI::drawStatus(const HudInfo &info, float x, float y) const {
  DrawTextEx(font, "Status: ", {x, y}, FONT_SIZE, SPACING, LABEL_COLOR);
  float width = MeasureTextEx(font, "Status: ", FONT_SIZE, SPACING).x;
  DrawTextEx(font, info.running ? "RUNNING" : "PAUSED",
             {x + width, y}, FONT_SIZE, SPACING,
             info.running ? RUN_COLOR : PAUSE_COLOR);
}
