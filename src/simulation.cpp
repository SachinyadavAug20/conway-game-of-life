#include "simulation.hpp"
#include <raylib.h>
#include <vector>
#include <utility>
using namespace std;

vector<pair<int, int>> neighbors = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                                    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

void Simulation::Draw() { grid.Draw(); }
void Simulation::SetCellValue(int row, int col, int val) {
  grid.SetValue(row, col, val);
}
int Simulation::CountLiveNeigbors(int row, int col) {
  int count = 0;
  for (auto &neighbor : neighbors) {
    int x = (row + neighbor.first + grid.getRows()) % grid.getRows();
    int y = (col + neighbor.second + grid.getcols()) % grid.getcols();
    if (grid.getCell(x, y) > 0) {
      count++;
    }
  }
  return count;
}
void Simulation::update() {
  if(IsRunning()==false) return;
  for (int row = 0; row < grid.getRows(); row++) {
    for (int col = 0; col < grid.getcols(); col++) {
      int val = grid.getCell(row, col);
      int liveNeigbors = CountLiveNeigbors(row, col);
      if(val==1){
        if(liveNeigbors>3 || liveNeigbors<2) tempGrid.SetValue(row, col, 0);
        else tempGrid.SetValue(row, col, 1);
      }else {
        if(liveNeigbors==3) tempGrid.SetValue(row, col, 1);
        else tempGrid.SetValue(row, col, 0);
      }
    }
  }
  grid=tempGrid;
}

void Simulation::ClearGride(){
  if(!IsRunning()) grid.clear();
}

void Simulation::CreateRandomState(){
  if(!IsRunning()) grid.FillRandomly();
}
void Simulation::ToggleCell(int row,int col){
  if(!IsRunning()) grid.ToggleCell(row,col);
}
