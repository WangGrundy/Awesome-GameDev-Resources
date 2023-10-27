#ifndef AWESOMECPPCOURSE_RANDOM_H
#define AWESOMECPPCOURSE_RANDOM_H
#include <random>
#include <cstdlib>

struct Random {
  //https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
  static int Range(int start, int end) {
    std::random_device dev; //set up engine
    std::mt19937 rng(dev()); //seed engine
    std::uniform_int_distribution<std::mt19937::result_type> dist(start,end);
    dist(rng);
  }
};

#endif  // AWESOMECPPCOURSE_RANDOM_H

//other distributions:
//std::uniform_int_distribution<uint32_t> uint_dist;         // by default range [0, MAX]
//std::uniform_int_distribution<uint32_t> uint_dist10(0,10); // range [0,10]
//std::normal_distribution<double> normal_dist(mean, stddeviation);  // N(mean, stddeviation)
