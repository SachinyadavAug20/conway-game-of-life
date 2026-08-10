#pragma once
#include "grid.hpp"

class Simulation {
public:
  Simulation(int width, int height, int cell_size)
      : width(width), height(height), grid(width, height, cell_size),
        tempGrid(width, height, cell_size), run(false), generation(0),
        liveCount(0), deadCount(0) {
    refreshCounts();
  }
  void Draw();
  void setCellValue(int row, int col, int val);
  void update();
  bool IsRunning() const { return run; }
  void toggleRunning() { run = !run; }
  void start() { run = true; }
  void stop() { run = false; }
  void ClearGrid();
  void createRandomState();
  void toggleCell(int row, int col);
  void resize(int cellSize);
  int getGeneration() const { return generation; }
  int getLiveCount() const { return liveCount; }
  int getDeadCount() const { return deadCount; }
  int getRows() const { return grid.getRows(); }
  int getCols() const { return grid.getCols(); }
  int getCellSize() const { return grid.getCellSize(); }

private:
  int countLiveNeighbors(int row, int col);
  void refreshCounts();

  int width;
  int height;
  Grid grid;
  Grid tempGrid;
  bool run;
  int generation;
  int liveCount;
  int deadCount;
};
