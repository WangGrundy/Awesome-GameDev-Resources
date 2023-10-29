#include "Cat.h"

pair<int,int> Cat::move(const vector<bool>& world, pair<int,int> catPos, int side) {
  Point2D catPositionDeQuantized = Point2D(catPos.first, catPos.second);
  vector<Point2D> path = generatePath(world, catPositionDeQuantized, side);

  if(path.empty()){
    Point2D randomTile = getRandomTileNextToCat(world, catPositionDeQuantized, side);
    cout << "\n\nrandom tile!\n\n";
    return {randomTile.x, randomTile.y};
  }

  cout << "\n\ntile selected\n\n";
  return {path[path.size()-1].x, path[path.size()-1].y};
}

std::vector<Point2D> Cat::generatePath(const vector<bool>& w, Point2D catPositionQuantized, int side){
  unordered_map<Point2D, Point2D> cameFrom; //new , old
  queue<Point2D> frontier; // to store next ones to visit
  unordered_set<Point2D> frontierSet; // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited; // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  frontier.push(catPositionQuantized);
  frontierSet.insert(catPositionQuantized);
  Point2D borderExit = Point2D::INFINITE; // if at the end of the loop we dont find a border, we have to return random points

  Point2D current;
  bool canWin = false;
  vector<Point2D> path;

  while (!frontier.empty()){
    // get the current from frontier
    current = frontier.front();

    // remove the current from frontierset
    frontierSet.erase(current);
    frontier.pop();

    // mark current as visited
    visited[current] = true;

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> neighbors = getVisitableNeightbors(w, current, catPositionQuantized, visited, frontierSet, side);

    // iterate over the neighs:
    for(auto point : neighbors){
      // for every neighbor set the cameFrom
      cameFrom[point] = current;

      // enqueue the neighbors to frontier and frontierset
      frontierSet.insert(point);
      frontier.emplace(point);
    }

    //break the loop if we can win
    if(catWinsOnSpace(current, side)){
      canWin = true;
      //setting the exit tile
      borderExit = current;
      break;
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  if(borderExit != Point2D::INFINITE){
    while(current != catPositionQuantized){
      path.push_back(current);

      //break if we reach the cat's position, do not add to path
      if(current == catPositionQuantized){
        break;
      }

      //Set previous node to this
      current = cameFrom[current]; //old point using new point
    }
  }

  // if there isn't a reachable border, just return empty vector
  if(!canWin){
    return vector<Point2D>();
  }

  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}

vector<Point2D> Cat::getVisitableNeightbors(const vector<bool>& world, Point2D current, Point2D catPositionDeQuantized, unordered_map<Point2D, bool> visited, unordered_set<Point2D> frontierSet, int side){

  // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited,
  // not cat, not block, not in the queue

  //get all neighbours of currentTile
  vector<Point2D> neighbours = current.Neighbors();
  vector<Point2D> visitableNeighbours;

  //Cycles through all neighbours that are visitable on next tile
  for(int i = 0; i <  neighbours.size(); i++){

    //if visited
    if(visited[neighbours[i]]){
      continue;
    }
    //if cat
    if(catPositionDeQuantized == neighbours[i]) {
      continue;
    }

    //if blocked
    if(getContent(neighbours[i], world, side)){
      continue;
    }

    //if its a duplicate in queue/frontierSet
    if(frontierSet.contains(neighbours[i])){
      continue;
    }

    //all checks complete... push to visitableNeighbours:
    visitableNeighbours.push_back(neighbours[i]);
  }

  return visitableNeighbours;
}

Point2D Cat::getRandomTileNextToCat(const vector<bool>& world, Point2D catPositionDeQuantized, int side){

  vector<Point2D> neighbours = catPositionDeQuantized.Neighbors();
  vector<Point2D> visitableNeighbours;

  //if there are 0 neighbours
  if(neighbours.empty()){
    return catPositionDeQuantized; //return itself
  }

  //check if we are able to move to this neighbour tile
  for(auto point : neighbours){
    if(catCanMoveToPosition(point, catPositionDeQuantized, world, side)){
      visitableNeighbours.push_back(point);
    }
  }

  //create a random number
  int rng = Random::Range(0,visitableNeighbours.size() - 1);

  return visitableNeighbours[rng];
}

Point2D Cat::randomTileInWorld(const vector<bool>& world, Point2D catPos, int side){
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};

    //if cat is not
    if (catPos.x != p.x && catPos.y != p.y && getContent(p, world, side)) {
      return p;
    }
  }
}