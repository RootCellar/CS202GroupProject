#ifndef TEAM_H
#define TEAM_H

class Team {

private:
  static int idPoint;

  int id;

public:
  Team() {
    id = idPoint++;
  }

  int getId() { return id; }
};

int idPoint = 0;

#endif
