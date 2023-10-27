#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include "Point2D.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "random.h"
#include <iostream>

using std::pair;
using std::vector;
using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::cout;

struct AStarNode {
  Point2D pos;
  float accumulatedCost;
  float heuristic;
  // for priority_queue
  bool operator < (const AStarNode& n) const{
    return this->accumulatedCost + this->heuristic < n.accumulatedCost + n.heuristic;
  }
};

struct Cat : public IAgent {

public:
  pair<int,int> frontier;
  pair<pair<int,int>,bool> visited; //coords, visited

  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override;
private:
  vector<Point2D> generatePath(const std::vector<bool>& world, Point2D catPos, int side);
  vector<Point2D> getVisitableNeightbors(const std::vector<bool>& world, Point2D current, Point2D catPosition, unordered_map<Point2D, bool> visited, unordered_set<Point2D> frontierSet, int side);
  Point2D getRandomTileNextToCat(const std::vector<bool>& world, Point2D catPos, int side);
  Point2D randomTileInWorld(const std::vector<bool>& world, Point2D catPos, int side);


  //turns 2D into 1D
  int Quantize(Point2D point, int side){
    return (point.y + side/2) * side + (point.x + side/2);
  }

//  //turns 1D into 2D
//  Point2D DeQuantize(int index, int side){
//
//    return Point2D(index / side, index % side);
//  }

  bool catWinsOnSpace(pair<int,int> position, int side){
    //abs will always make it positive, so comparing it to max, side as the win condition
      return abs(position.first) == side/2 || abs(position.second) == side/2;
  }

  bool catWinsOnSpace(Point2D position, int side){
      //abs will always make it positive, so comparing it to max, side as the win condition
      return abs(position.x) == side/2 || abs(position.y) == side/2;
  }

  bool isTileInBoard(const Point2D& catPositionDeQuantised, int side){

     //if X is larger than side
     if(!abs(catPositionDeQuantised.x) < side){
        return false;
     }

     //if Y is larger than side
     if(!abs(catPositionDeQuantised.y) < side){
        return false;
     }

     //conditions met, tile is inside board!
     return true;
  }

  //find out if this tile is blocked or not
  bool getContent(const Point2D& position, const std::vector<bool>& world, const int& side){

     int positionQuantized = Quantize(position, side);

     //return bool whether world vector = position
     return world[positionQuantized]; //only return true if blocked
  }

  bool isNeighbour(const Point2D& position1, const Point2D& position2, const std::vector<bool>& world, const int& side){
     vector<Point2D> neighbours = position1.Neighbors();

     //go through all neighbours, trying to find if our position2 is near position 1
     for(auto point : neighbours){
        if(position2 == point){
          return true;
        }
     }

     //if not found in neighbour list, return false
     return false;
  }

  bool catCanMoveToPosition(const Point2D& position, const Point2D& catPositionDeQuantized, const std::vector<bool>& world, const int& side){

     //if we are not a neighbour
     if(!isNeighbour(position, catPositionDeQuantized, world, side)){
          return false;
     }

     //if blocked
     if(getContent(position, world, side)){
          return false;
     }

     return true;
  }
};
#endif

