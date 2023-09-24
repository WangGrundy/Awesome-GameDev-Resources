#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

//structs
struct Vector2{
  Vector2(int x, int y) : x(x), y(y){};
  int x = 0;
  int y = 0;
  Vector2 Up() const{ return {x,y -1};};
  Vector2 Down() const{ return {x,y+1};};
  Vector2 Left() const{ return {x-1,y};};
  Vector2 Right() const{ return {x+1,y};};
};

using std::vector;
using std::cout, std::endl;
using std::this_thread::sleep_for;
using std::chrono::seconds, std::chrono::milliseconds;
using std::string;

//prototypes
std::vector<std::vector<string>> CreateMap(const int& mapSize, const std::vector<Vector2>& addTiles);
void AddTiles(std::vector<std::vector<string>>&, const std::vector<Vector2>&);
void PrintMap(const std::vector<std::vector<string>>& map, const int& mapSize);
int CountNeighbors(std::vector<std::vector<string>>& map, Vector2 point);
bool Get(std::vector<std::vector<string>>& map, Vector2 point);
void Step(vector<vector<string>>& currentMap, vector<Vector2>& addTiles, const int& mapSize);
void ResetMap(vector<vector<string>>& currentMap, const int& mapSize);

int main(){

    vector<Vector2> addTilesCurrent;
    vector<Vector2> addTilesEmpty; //empty

    //glider
    addTilesCurrent.emplace_back(1,3);
    addTilesCurrent.emplace_back(2,3);
    addTilesCurrent.emplace_back(3,3);
    addTilesCurrent.emplace_back(3,2);
    addTilesCurrent.emplace_back(2,1);

    int mapSize = 20;
    vector<vector<string>> currentMap, nextMap;

    //create maps
    currentMap = CreateMap(mapSize, addTilesCurrent);
    nextMap = CreateMap(mapSize, addTilesEmpty);

    PrintMap(currentMap, mapSize); //print initial

    //cycle (gameloop)
    while(true){
      cout << "--------------------------------------------------------------------\n";

      //step
      Step(currentMap, addTilesCurrent, mapSize);

      //print
      PrintMap(currentMap, mapSize);

      //add alive tiles to next map
      AddTiles(nextMap, addTilesCurrent);

      ResetMap(currentMap, mapSize);

      //wait
      sleep_for(seconds(1));

      currentMap = nextMap;
    }

  return 0;
};

vector<vector<string>> CreateMap(const int& mapSize, const vector<Vector2>& addTiles){

  //create 2D vector to store map results and initiate size of 2D vector
  vector<vector<string>> map(mapSize, vector<string>(mapSize));

  int counter = 0;

  for(int y = 0; y < mapSize; y++){
    for(int x = 0; x < mapSize; x++){
      map[x][y] = ".";
      counter++;
    }
  }

  AddTiles(map, addTiles);

  return map;
}

void AddTiles(vector<vector<string>>& map, const vector<Vector2>& tiles){
  for(auto tile : tiles){
    map[tile.x][tile.y] = "#";
  }
}

//print map probably
void PrintMap(const vector<vector<string>>& map, const int& mapSize){
  for (int y = 0; y < mapSize; y++){

    for (int x = 0; x < mapSize; x++){

      //print out map x and y result.
      std::cout << map[x][y] << " ";
    }

    //spacing
    std::cout << std::endl;
  }
}

int CountNeighbors(vector<vector<string>>& map, Vector2 point) {
  //TOP LEFT IS 0,0
  int neighbourCount = 0;
  Vector2 top = point.Up().Left();
  Vector2 middle = point.Left();
  Vector2 bottom = point.Down().Left();

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

bool Get(vector<vector<string>>& map, Vector2 point){
  if(point.x < 0 || point.x >= map.size()){
    return false;
  }
  if(point.y < 0 || point.y >= map.size()){
    return false;
  }

  if(map[point.x][point.y] == "#"){
    return true;
  }
  else{
    return false;
  }
}

void Step(vector<vector<string>>& currentMap, vector<Vector2>& addTiles, const int& mapSize) {
  Vector2 currentLocation = {0, 0};
  int numberOfNeighbours = 0;
  bool isAlive = false;

  //on reset
  addTiles.clear(); // clear the array of added tiles for this time

  //go through map
  for (int y = 0; y < mapSize; y++) {
    for (int x = 0; x < mapSize; x++) {
      currentLocation = Vector2(x, y);
      numberOfNeighbours = CountNeighbors(currentMap, currentLocation);
      isAlive = Get(currentMap, currentLocation);

      //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      //Any live cell with two or three live neighbours lives on to the next generation.
      //Any live cell with more than three live neighbours dies, as if by overpopulation.
      //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

      if (isAlive) {  // if alive
        // Each cell with two or three neighbors survives.
        if (numberOfNeighbours == 2 || numberOfNeighbours == 3) {
          addTiles.emplace_back(x,y);
        }
      }
      else {  // if dead
        // Each cell with three neighbors becomes populated.
        if (numberOfNeighbours == 3) {
          addTiles.emplace_back(x, y);
        }
      }
    }
  }
}

void ResetMap(vector<vector<string>>& currentMap, const int& mapSize){
  for(int y = 0; y < mapSize; y++){
    for(int x = 0; x < mapSize; x++){
      currentMap[x][y] = ".";
    }
  }
}

