#pragma once
#include <utility>
#include <vector>

struct Pattern {
  const char *name;
  const char *desc;
  int cellSize;
  int fps;
  const char *rle;
};

inline std::vector<std::pair<int, int>> parseRle(const char *rle) {
  std::vector<std::pair<int, int>> cells;
  int row = 0, col = 0, count = 0;
  for (const char *c = rle; *c != '\0' && *c != '!'; c++) {
    if (*c >= '0' && *c <= '9') {
      count = count * 10 + (*c - '0');
    } else if (*c == 'b') {
      col += count == 0 ? 1 : count;
      count = 0;
    } else if (*c == 'o') {
      int n = count == 0 ? 1 : count;
      for (int i = 0; i < n; i++) cells.push_back({row, col + i});
      col += n;
      count = 0;
    } else if (*c == '$') {
      row += count == 0 ? 1 : count;
      col = 0;
      count = 0;
    }
  }
  return cells;
}

const Pattern PRESETS[7] = {
    {"Glider", "smallest c/4 diagonal spaceship", 15, 6,
     "bo$2bo$3o!"},
    {"Lightweight Spaceship", "orthogonal c/2 spaceship", 15, 6,
     "bo2bo$o4b$o3bo$4o!"},
    {"Gosper Glider Gun", "fires a glider every 30 generations", 12, 12,
     "24bo$22bobo$12b2o6b2o12b2o$11bo3bo4b2o12b2o$2o8bo5bo3b2o$2o8bo3bob2o"
     "4bobo$10bo5bo7bo$11bo3bo$12b2o!"},
    {"Pulsar", "period-3 oscillator, 4-fold symmetry", 30, 10,
     "2b3o3b3o2$o4bobo4bo$o4bobo4bo$o4bobo4bo$2b3o3b3o2$2b3o3b3o$o4bobo4bo$"
     "o4bobo4bo$o4bobo4bo2$2b3o3b3o!"},
    {"Pentadecathlon", "period-15 oscillator", 30, 10,
     "2bo4bo$2ob4ob2o$2bo4bo!"},
    {"R-pentomino", "methuselah, 1103 generations", 8, 24,
     "b2o$2o$bo!"},
    {"Acorn", "methuselah, 5206 generations", 8, 24,
     "bo5b$3bo3b$2o2b3o!"},
};
