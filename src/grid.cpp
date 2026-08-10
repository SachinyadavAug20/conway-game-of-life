#include "grid.hpp"
#include "raylib.h"

void Gride::Draw() {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      Color color =
          cells[row][col] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
      DrawRectangle(col * cell_size, row * cell_size, cell_size - 1,
                    cell_size - 1, color);
    }
  }
}
void Gride::SetValue(int row, int col, int value) {
  if (IsWithinBounds(row, col))
    cells[row][col] = value;
}
int Gride::getCell(int row, int col) {
  if (IsWithinBounds(row, col))
    return cells[row][col];
  return -1;
}
bool Gride::IsWithinBounds(int row, int col) {
  return (row >= 0 && row < rows && col >= 0 && col < cols);
}
void Gride::FillRandomly() {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int random = GetRandomValue(0, 4);
      cells[row][col] = random == 4 ? 1 : 0;
    }
  }
}
void Gride::clear() {
  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++)
      cells[row][col] = 0;
}
void Gride::ToggleCell(int row, int col) {
  if (IsWithinBounds(row, col))
    cells[row][col] = !cells[row][col];
}
