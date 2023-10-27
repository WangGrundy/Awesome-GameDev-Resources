#ifndef CATCHER_H
#define CATCHER_H
#include "IAgent.h"
#include <queue>
#include <vector>
#include <cstdint> //has int32_t in

using std::vector;
using std::pair;
using std::queue;

struct Catcher : public IAgent {

public:
  pair<int,int> move(const vector<bool>& world, pair<int,int> catPos, int sideSize ) override;

protected:
private:
  queue<pair<int, int>> outerQueue;
  bool finishedFirstRun = false;
};
#endif