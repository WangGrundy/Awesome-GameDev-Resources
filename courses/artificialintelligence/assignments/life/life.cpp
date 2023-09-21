#include <iostream>
#include <vector>
#include <array>

//structs
struct Vector2f{
  Vector2f(int x, int y) : x(x), y(y){};
  float x = 0;
  float y = 0;
  Vector2f Up(){ return Vector2f(x,y -1);};
  Vector2f Down(){ return Vector2f(x,y+1);};
  Vector2f Left(){ return Vector2f(x,y-1);};
  Vector2f Right(){ return Vector2f(x+1,y);};
};

//prototypes
std::vector<std::vector<int>> CreateMap(const int& mapSize, const std::vector<Vector2f>& addTiles);
void AddTiles(std::vector<std::vector<int>>&, const std::vector<Vector2f>&);
void PrintMap(const std::vector<std::vector<int>>& map, const int& mapSize);
int CountNeighbors(std::vector<std::vector<int>>& map, Vector2f point);
bool Get(std::vector<std::vector<int>>& map, Vector2f point);

int main(){

    Vector2f tile1(3,3);
    std::vector<Vector2f> addTiles;
    addTiles.push_back(tile1);

    int mapSize = 5;
    std::vector<std::vector<int>> map;
    map = CreateMap(mapSize, addTiles);
    //AddTiles(tilesAdded);

    //std::cout << map[0][0] << map[1][0];

    PrintMap(map, mapSize);

  return 0;
};

//prototypes
std::vector<std::vector<int>> CreateMap(const int& mapSize, const std::vector<Vector2f>& addTiles){

  //create 2D vector to store map results and initiate size of 2D vector
  std::vector<std::vector<int>> map(mapSize, std::vector<int>(mapSize));

  int counter = 0;

  for(int y = 0; y < mapSize; y++){
    for(int x = 0; x < mapSize; x++){
      map[x][y] = 0;
      counter++;
    }
  }

  AddTiles(map, addTiles);

  return map;
}

void AddTiles(std::vector<std::vector<int>>& map, const std::vector<Vector2f>& tiles){
  for(int i = 0; i < tiles.size(); i++){
    map[tiles[i].x][tiles[i].y] = 1;
  }
}

//print map probably
void PrintMap(const std::vector<std::vector<int>>& map, const int& mapSize){
  for (int y = 0; y < mapSize; y++){

    for (int x = 0; x < mapSize; x++){

      //print out map x and y result.
      std::cout << map[x][y] << " ";
    }

    //spacing
    std::cout << std::endl;
  }
}

int CountNeighbors(std::vector<std::vector<int>>& map, Vector2f point) {
  //TOP LEFT IS 0,0
  int neighbourCount = 0;
  Vector2f top = point.Up().Left();
  Vector2f middle = point.Left();
  Vector2f bottom = point.Down().Left();

  if(Get(map,point.Up())){
    neighbourCount++;
  }
  if(Get(map,point.Down())){
    neighbourCount++;
  }

  if(Get(map,point.Up().Left())){
    neighbourCount++;
  }
  if(Get(map,point.Left())){
    neighbourCount++;
  }
  if(Get(map,point.Down().Left())){
    neighbourCount++;
  }

  if(Get(map,point.Up().Right())){
    neighbourCount++;
  }
  if(Get(map,point.Right())){
    neighbourCount++;
  }
  if(Get(map,point.Down().Right())){
    neighbourCount++;
  }

  return neighbourCount;
}

bool Get(std::vector<std::vector<int>>& map, Vector2f point){
  if(map[point.x][point.y]){
    return true;
  }
  else{
    return false;
  }
}

void Step(std::vector<std::vector<int>>& map, const int& mapSize) {
  Vector2f currentLocation = {0, 0};
  int numberOfNeighbours = 0;
  bool isAlive = false;

  for (int i = 0; i < mapSize; i++) {
    for (int j = 0; j < mapSize; j++) {
      currentLocation = Vector2f(j, i);
      numberOfNeighbours = CountNeighbors(map, currentLocation);
      isAlive = Get(map, currentLocation);

      //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      //Any live cell with two or three live neighbours lives on to the next generation.
      //Any live cell with more than three live neighbours dies, as if by overpopulation.
      //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
//
//      if (isAlive) {  // if alive
//        //Each cell with one or no neighbors dies, as if by solitude.
//        if (numberOfNeighbours <= 1) {
//          world.SetNext(currentLocation, false);
//        }
//        // Each cell with two or three neighbors survives.
//        else if (numberOfNeighbours == 2 || numberOfNeighbours == 3) {
//          world.SetNext(currentLocation, true);
//        }
//        // Each cell with four or more neighbors dies, as if by overpopulation.
//        else if (numberOfNeighbours >= 4) {
//          world.SetNext(currentLocation, false);
//        }
//
//      }
//      else if (!isAlive) {  // if dead
//        // Each cell with three neighbors becomes populated.
//        if (numberOfNeighbours == 3) {
//          world.SetNext(currentLocation, true);
//        }
//      }
    }
  }
}