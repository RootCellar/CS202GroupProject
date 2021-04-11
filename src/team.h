#ifndef TEAM_H
#define TEAM_H

class Team {

private:
  static int idPoint;

  int id;
  bool alone;

public:
  Team();

  //Don't set a real ID for this team if this team is marked as being "alone"
  Team(bool a);

  int getId() const;

  bool isAlone() const;
};

#endif
