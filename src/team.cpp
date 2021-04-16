
#include "team.h"

Team::Team(): alone(false) {
  id = idPoint++;
}

//Don't set a real ID for this team if this team is marked as being "alone"
Team::Team(bool a): alone(a) {
  if(!alone) {
    id = idPoint++;
  }
  else id = -1;
}

int Team::getId() const { return id; }

bool Team::isAlone() const { return alone; }

//If either team is "alone", return false
//otherwise, return true if IDs match, false otherwise
bool operator==(const Team& one, const Team& two) {
  if(one.isAlone() || two.isAlone()) return false;
  return one.getId() == two.getId();
}

bool operator!=(const Team& one, const Team& two) {
  return !(one == two);
}

int Team::idPoint = 0;
