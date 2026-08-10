#pragma once
#include <algorithm>
#include <vector>

class Grid {
public:
  Grid(int width, int height, int cell_size)
      : cell_size(std::max(1, cell_size)),
        rows(std::max(1, height / std::max(1, cell_size))),
        cols(std::max(1, width / std::max(1, cell_size))),
        cells(rows, std::vector<int>(cols, 0)) {}
  void Draw();
  void setValue(int row, int col, int value);
  int getCell(int row, int col) const;
  bool isWithinBounds(int row, int col) const;
  int getRows() const { return rows; }
  int getCols() const { return cols; }
  int getCellSize() const { return cell_size; }
  void fillRandomly();
  void clear();
  void toggleCell(int row, int col);
  int getLiveCount() const;

private:
  int cell_size;
  int rows;
  int cols;
  std::vector<std::vector<int>> cells;
};
