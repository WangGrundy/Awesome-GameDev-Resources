// add your imports
#include <vector>
#include <iostream>
using namespace std;

vector<bool> verticals, horizontals, visited;

struct Point2D{
  int x, y;
};

Point2D limits;

void generateMap(Point2D limits){
  verticals.resize((limits.x + 1) * (limits.y + 1));
  horizontals.reserve((limits.x + 1) * (limits.y + 1));
  visited.resize(limits.x * limits.y);

  for(int i = 0; i < visited.size(); i++){
    visited[i] = false;
  }

  for(int i = 0; i < horizontals.size(); i++){
    horizontals[i] = true;
  }

  for(int i = 0; i < verticals.size(); i++){
    verticals[i] = true;
  }


}

enum class Direction{
  Up = 0,
  Right = 1,
  Down = 2,
  Left = 3
};

bool isThereWall(Point2D p, Direction d){
  switch(d){
    case Direction::Up :
      //matrix linarisation , double pointers are slow?
      return verticals[limits.x * p.y + p.x];
      break;
    case Direction::Right :
      return horizontals[limits.x * p.y + (p.x + 1)];
      break;
    case Direction::Down :
      return horizontals[limits.x * (p.y + 1) + p.x];
      break;
    case Direction::Left :
      return horizontals[limits.x + p.y + p.x ];
      break;
  }

}

bool getVisited(Point2D p){
  return visited[limits.x * p.y + p.x];
}

void setVisited(Point2D p, bool state){
  visited[limits.x * p.y + p.x] = state;
}

vector<Point2D> getVisitables(Point2D p){

}

int main(){
  // code here

}