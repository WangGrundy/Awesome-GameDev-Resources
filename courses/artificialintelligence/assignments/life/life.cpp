#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <thread>

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
using std::cout, std::endl;
using std::this_thread::sleep_for;
using std::chrono::seconds, std::chrono::milliseconds;

//prototypes
std::vector<std::vector<int>> CreateMap(const int& mapSize, const std::vector<Vector2f>& addTiles);
void AddTiles(std::vector<std::vector<int>>&, const std::vector<Vector2f>&);
void PrintMap(const std::vector<std::vector<int>>& map, const int& mapSize);
int CountNeighbors(std::vector<std::vector<int>>& map, Vector2f point);
bool Get(std::vector<std::vector<int>>& map, Vector2f point);
void Step(vector<vector<int>>& currentMap, vector<Vector2f>& addTiles, const int& mapSize);

int main(){

    vector<Vector2f> addTilesCurrent;
    vector<Vector2f> addTilesEmpty; //empty

    //glider
    addTilesCurrent.push_back(Vector2f(1,3));
    addTilesCurrent.push_back(Vector2f(2,3));
    addTilesCurrent.push_back(Vector2f(3,3));
    addTilesCurrent.push_back(Vector2f(3,2));
    addTilesCurrent.push_back(Vector2f(2,1));

    int mapSize = 20;
    vector<vector<int>> currentMap, nextMap;

    //create maps
    currentMap = CreateMap(mapSize, addTilesCurrent);
    nextMap = CreateMap(mapSize, addTilesEmpty);


    //print map

    //cycle (gameloop)
    while(true){
      cout << "--------------------------------------------------------------------\n";
      //print


      //alternate which map we are printing
      PrintMap(currentMap, mapSize);

      //step
      Step(currentMap, addTilesCurrent, mapSize);

      //add alive tiles
      AddTiles(nextMap, addTilesCurrent);

      //wait
      sleep_for(seconds(3));

      currentMap = nextMap;
    }


  return 0;
};

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

//  cout << "BEFORE:\n";
//  cout << "X:" << point.y << "Y:" << point.x << endl;
//  cout << "AFTER\n";
//  cout << "X:" << point.Up().x << "Y:" << point.Up().y << endl;

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
  if(point.x < 0 || point.x >= map.size()){
    return false;
  }
  if(point.y < 0 || point.y >= map.size()){
    return false;
  }

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

  //on reset
  addTiles.clear(); // clear the array of added tiles for this time

  //go through map
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