#ifndef PATH_HPP
#define PATH_HPP

#include "Location.hpp"
#include "TerrainType.hpp"

using namespace std;

class Location;

// Path representing a connection between two locations
// Constructor: {string Name, Terraintype terrain, Location, Location}
class Path {
  friend class Location;
  friend class Route;
  private:  
    string pathname; // Name of path (i.e. Sheldon Road)
    TerrainType terrain; // Type of terrain (i.e. Grass) (represented by enum TerrainType)
    Location* start; // start
    Location* dest; // destination
    double distance; // distance (in meters)
    // Safety level, frequency and other variables
  public:
    // Default constructor 
    Path(string name_in, TerrainType ter_in, Location* loc_a, Location* loc_b);
    // Normal Copy ctor
    Path(const Path& other);
    // Copy ctor (if reverse, true it flips Path)
    Path(const Path& other, bool reverse);

    string str(bool concise=false) const;

    bool operator==(const Path& other) {
      return ((other.start==start&&other.dest==dest)||(other.start==dest&&other.dest==start));
    }
    bool operator==(const pair<Coordinates, Coordinates> &coords) {
      return ((start->coords==coords.first&&dest->coords==coords.second)||(start->coords==coords.second&&dest->coords==coords.first));
    }
    // MAYBE NEED == WITH LOCATION*'s
    Location* operator*() {
      return dest;
    }
};

class PathAlreadyExists: public std::exception {
  private: 
    string errorMessage;
  public:
    PathAlreadyExists(const Path &p) {
      errorMessage = "Path already exists.\n"+p.str();
    } 
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

#endif // PATH_HPP