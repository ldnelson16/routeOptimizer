#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <vector>

using namespace std;

// FORWARD DECLARATIONS
class Path;
class Location;

class Route {
  friend class GeoMap;
  private: 
    vector<Path*> paths;
  public: 
    Route (vector<Path*> paths_in): paths(paths_in) {}
    bool inRoute(Location* loc);
};

#endif // ROUTE_HPP