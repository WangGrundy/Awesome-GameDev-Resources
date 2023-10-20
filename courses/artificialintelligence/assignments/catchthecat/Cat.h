#ifndef CAT_h
#define CAT_h
#include "IAgent.h"

using std::pair;

struct Cat : public IAgent {

  pair<int,int> frontier;
  pair<pair<int,int>,bool> visited; //coords, visited

  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{

        return {1,0}; // todo: change this
  }
};
#endif