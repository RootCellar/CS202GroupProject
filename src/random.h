#ifndef RANDOM_H
#define RANDOM_H

#include <random>

using std::mt19937;
using std::random_device;

class Random {

private:

  static random_device dev;
  static mt19937 gen;

public:

  static auto getGen() { return gen; }

};

#endif
