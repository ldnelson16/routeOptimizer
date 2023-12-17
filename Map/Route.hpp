#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <vector>
#include <string>

using namespace std;

// FORWARD DECLARATIONS
class Path;
class Location;

class Route {
  friend class GeoMap;
  friend class Location;
  friend class CompareLocations;
  private: 
    vector<Path*> paths;
    double distance;
  public: 
    Route (vector<Path*> paths_in);
    bool inRoute(Location* loc) const;
    bool operator<(const Route& other) {
      if (distance==other.distance) {return paths.size() < other.paths.size();}
      else {return distance < other.distance;}
    }
    void operator+=(const Route& other) {
      paths.insert(paths.end(),other.paths.begin(),other.paths.end());
      distance += other.distance;
    }
    bool contains(Location* loc) const;
};

class NoRouteExists: public std::exception {
  private:
    string errorMessage;
  public:
    NoRouteExists(Location* start, Location* end);
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

#endif // ROUTE_HPP