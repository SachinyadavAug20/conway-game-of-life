#include "grid.hpp"
#include "raylib.h"

void Gride::Draw() {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      Color color = cells[row][col] == 0 ? Color{0, 0, 0, 255} : Color{55, 55, 55, 255};
      DrawRectangle(col * cell_size, row * cell_size, cell_size, cell_size, color);
    }
  }
}
