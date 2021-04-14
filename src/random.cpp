#include "random.h"
#include <random>

mt19937 Random::gen(Random::dev());

int randInt(int min, int max) {
  std::uniform_int_distribution<int> dist(min,max);
  return dist(Random::getGen());
}
