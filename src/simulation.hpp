#pragma once
#include "grid.hpp"

class Simulation {
public:
  Simulation(int width, int height, int cell_size)
      : grid(width, height, cell_size), tempGrid(width, height, cell_size),
        run(false) {};
  void Draw();
  void SetCellValue(int row, int col, int val);
  int CountLiveNeigbors(int row, int col);
  void update();
  bool IsRunning() { return run; }
  void start() { run = true; }
  void stop() { run = false; }
  void ClearGride();
  void CreateRandomState();
  void ToggleCell(int row, int col);

private:
  Gride grid;
  Gride tempGrid;
  bool run;
};
