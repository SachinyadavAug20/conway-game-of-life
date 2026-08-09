#include "simulation.hpp"
#include <vector>
using namespace std;

vector<pair<int, int>> neighbors = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                                    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

void Simulation::Draw() { grid.Draw(); }
void Simulation::SetCellValue(int row, int col, int val) {
  grid.SetValue(row, col, val);
}
int Simulation::CountLiveNeigbors(int row, int col) {
  int count = 0;
  for (auto neighbor : neighbors) {
    int x = row + neighbor.first;
    int y = col + neighbor.second;
    if (grid.getCell(x, y) >0) {
      count++;
    }
  }
  return count;
}
