#include "simulation.hpp"
#include <raylib.h>
#include <algorithm>
#include <utility>

namespace {
const std::pair<int, int> neighbors[] = {
    {-1, 0}, {1, 0},  {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
}

void Simulation::Draw() { grid.Draw(); }

void Simulation::setCellValue(int row, int col, int val) {
  grid.setValue(row, col, val);
}

int Simulation::countLiveNeighbors(int row, int col) {
  int count = 0;
  int rows = grid.getRows();
  int cols = grid.getCols();
  for (const auto &neighbor : neighbors) {
    int x = (row + neighbor.first + rows) % rows;
    int y = (col + neighbor.second + cols) % cols;
    if (grid.getCell(x, y) > 0) {
      count++;
    }
  }
  return count;
}

void Simulation::update() {
  if (!IsRunning()) return;
  for (int row = 0; row < grid.getRows(); row++) {
    for (int col = 0; col < grid.getCols(); col++) {
      int val = grid.getCell(row, col);
      int liveNeighbors = countLiveNeighbors(row, col);
      if (val == 1) {
        if (liveNeighbors > 3 || liveNeighbors < 2)
          tempGrid.setValue(row, col, 0);
        else
          tempGrid.setValue(row, col, 1);
      } else {
        if (liveNeighbors == 3)
          tempGrid.setValue(row, col, 1);
        else
          tempGrid.setValue(row, col, 0);
      }
    }
  }
  std::swap(grid, tempGrid);
  generation++;
  refreshCounts();
}

void Simulation::refreshCounts() {
  liveCount = grid.getLiveCount();
  deadCount = grid.getRows() * grid.getCols() - liveCount;
}

void Simulation::ClearGrid() {
  if (!IsRunning()) {
    grid.clear();
    generation = 0;
    refreshCounts();
  }
}

void Simulation::createRandomState() {
  if (!IsRunning()) {
    grid.fillRandomly();
    generation = 0;
    refreshCounts();
  }
}

void Simulation::toggleCell(int row, int col) {
  if (!IsRunning()) {
    grid.toggleCell(row, col);
    refreshCounts();
  }
}

void Simulation::resize(int cellSize) {
  int oldRows = grid.getRows();
  int oldCols = grid.getCols();
  Grid newGrid(width, height, cellSize);
  Grid newTemp(width, height, cellSize);
  int copyRows = std::min(oldRows, newGrid.getRows());
  int copyCols = std::min(oldCols, newGrid.getCols());
  for (int row = 0; row < copyRows; row++) {
    for (int col = 0; col < copyCols; col++) {
      newGrid.setValue(row, col, grid.getCell(row, col));
    }
  }
  grid = newGrid;
  tempGrid = newTemp;
  generation = 0;
  refreshCounts();
}

void Simulation::loadPattern(const Pattern &p) {
  stop();
  resize(p.cellSize);
  grid.clear();

  auto cells = parseRle(p.rle);
  int patRows = 0, patCols = 0;
  for (const auto &cell : cells) {
    patRows = std::max(patRows, cell.first + 1);
    patCols = std::max(patCols, cell.second + 1);
  }
  int offsetRow = std::max(0, (grid.getRows() - patRows) / 2);
  int offsetCol = std::max(0, (grid.getCols() - patCols) / 2);
  for (const auto &cell : cells) {
    grid.setValue(offsetRow + cell.first, offsetCol + cell.second, 1);
  }

  generation = 0;
  refreshCounts();
}
