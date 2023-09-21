#include <iostream>
#include <vector>
#include <array>

//structs
struct Vector2f{
  Vector2f(int x, int y, bool alive) : x(x), y(y), alive(alive){};
  float x = 0;
  float y = 0;
  bool alive = false;
};

//prototypes
std::vector<std::vector<int>> CreateMap(const int& mapSize, const std::vector<Vector2f>& addTiles);
void AddTiles(std::vector<std::vector<int>>&, const std::vector<Vector2f>&);
void PrintMap(const std::vector<std::vector<int>>& map, const int& mapSize);

int main(){

    Vector2f tile1(3,3, true);
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

