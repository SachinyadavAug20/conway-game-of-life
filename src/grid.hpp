#pragma once
#include <vector>
using namespace std;

class Gride {
public:
  Gride(int width, int height, int cell_size)
      : rows(height / cell_size), cols(width / cell_size), cell_size(cell_size),
        cells(rows, vector<int>(cols, 0)) {}
  void Draw();
  void SetValue(int row, int col, int value);
  int getCell(int row, int col);
  bool IsWithinBounds(int row, int col);

private:
  int rows;
  int cols;
  int cell_size;
  vector<vector<int>> cells;
};
