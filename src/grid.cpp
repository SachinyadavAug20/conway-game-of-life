#include "grid.hpp"
#include "raylib.h"
#include <algorithm>

void Grid::Draw() {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      Color color =
          cells[row][col] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
      DrawRectangle(col * cell_size, row * cell_size, cell_size - 1,
                    cell_size - 1, color);
    }
  }
}
void Grid::setValue(int row, int col, int value) {
  if (isWithinBounds(row, col))
    cells[row][col] = value;
}
int Grid::getCell(int row, int col) const {
  if (isWithinBounds(row, col))
    return cells[row][col];
  return -1;
}
bool Grid::isWithinBounds(int row, int col) const {
  return (row >= 0 && row < rows && col >= 0 && col < cols);
}
void Grid::fillRandomly() {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int random = GetRandomValue(0, 4);
      cells[row][col] = random == 4 ? 1 : 0;
    }
  }
}
void Grid::clear() {
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++)
      cells[row][col] = 0;
}
void Grid::toggleCell(int row, int col) {
  if (isWithinBounds(row, col))
    cells[row][col] = !cells[row][col];
}
int Grid::getLiveCount() const {
  int count = 0;
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++)
      count += cells[row][col];
  return count;
}
