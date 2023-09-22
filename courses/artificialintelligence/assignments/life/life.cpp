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

using std::vector;
using std::cout;

//prototypes
std::vector<std::vector<int>> CreateMap(const int& mapSize, const std::vector<Vector2f>& addTiles);
void AddTiles(std::vector<std::vector<int>>&, const std::vector<Vector2f>&);
void PrintMap(const std::vector<std::vector<int>>& map, const int& mapSize);
int CountNeighbors(std::vector<std::vector<int>>& map, Vector2f point);
bool Get(std::vector<std::vector<int>>& map, Vector2f point);
void Step(vector<vector<int>>& currentMap, vector<Vector2f>& addTiles, const int& mapSize);

int main(){

    Vector2f tile1(3,3);
    vector<Vector2f> addTiles;
    vector<Vector2f> addTiles2;
    addTiles.push_back(tile1);

    int mapSize = 5;
    vector<vector<int>> currentMap, nextMap;
    currentMap = CreateMap(mapSize, addTiles);

    nextMap = CreateMap(mapSize, addTiles2);
    //AddTiles(tilesAdded);

    //std::cout << map[0][0] << map[1][0];

    PrintMap(currentMap, mapSize);

  return 0;
};

//prototypes
vector<vector<int>> CreateMap(const int& mapSize, const vector<Vector2f>& addTiles){

  //create 2D vector to store map results and initiate size of 2D vector
  vector<vector<int>> map(mapSize, vector<int>(mapSize));

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

void AddTiles(vector<vector<int>>& map, const vector<Vector2f>& tiles){
  for(int i = 0; i < tiles.size(); i++){
    map[tiles[i].x][tiles[i].y] = 1;
  }
}

//print map probably
void PrintMap(const vector<vector<int>>& map, const int& mapSize){
  for (int y = 0; y < mapSize; y++){

    for (int x = 0; x < mapSize; x++){

      //print out map x and y result.
      std::cout << map[x][y] << " ";
    }

    //spacing
    std::cout << std::endl;
  }
}

int CountNeighbors(vector<vector<int>>& map, Vector2f point) {
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

bool Get(vector<vector<int>>& map, Vector2f point){
  if(map[point.x][point.y]){
    return true;
  }
  else{
    return false;
  }
}

void Step(vector<vector<int>>& currentMap, vector<Vector2f>& addTiles, const int& mapSize) {
  Vector2f currentLocation = {0, 0};
  int numberOfNeighbours = 0;
  bool isAlive = false;

  addTiles.clear(); // clear the array of added tiles for this time

  for (int y = 0; y < mapSize; y++) {
    for (int x = 0; x < mapSize; x++) {
      currentLocation = Vector2f(x, y);
      numberOfNeighbours = CountNeighbors(currentMap, currentLocation);
      isAlive = Get(currentMap, currentLocation);

      //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      //Any live cell with two or three live neighbours lives on to the next generation.
      //Any live cell with more than three live neighbours dies, as if by overpopulation.
      //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

      if (isAlive) {  // if alive
        // Each cell with two or three neighbors survives.
        if (numberOfNeighbours == 2 || numberOfNeighbours == 3) {
          addTiles.push_back(Vector2f(x,y));
        }
      }
      else if (!isAlive) {  // if dead
        // Each cell with three neighbors becomes populated.
        if (numberOfNeighbours == 3) {
          addTiles.push_back(Vector2f(x,y));
        }
      }
    }
  }
}