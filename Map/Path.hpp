#ifndef PATH_HPP
#define PATH_HPP

#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <utility>
#include "Location.hpp"

using namespace std;

class Location;

// Variable to represent type of terrain
enum TerrainType { 
  Paved,
  Gravel,
  Dirt,
  Grass
};

// Path representing a connection between two locations
// Constructor: {string Name, Terraintype terrain, Location, Location}
class Path {
  using vertices = pair<const Location*,const Location*>;
  public:
    string pathname; // Name of path (i.e. Sheldon Road)
    TerrainType terrain; // Type of terrain (i.e. Grass) (represented by enum TerrainType)
    vertices startendpair;
    // Safety level, frequency and other variables

    // Default constructor 
    Path(string name_in, TerrainType ter_in, const Location* loc_a, const Location* loc_b);
    // Copy ctor (used to reverse Path)
    Path(const Path& reverse);

    string str(bool concise=false) const;

    bool operator==(const Path& other) {
      return (*(startendpair.first)==*(other.startendpair.first)&&*(startendpair.second)==*(other.startendpair.second))||(*(startendpair.first)==*(other.startendpair.second)&&*(startendpair.second)==*(other.startendpair.first));
    }
    bool operator==(const pair<const Location,const Location> locs) {
      return true;
    }
};

#endif // PATH_HPP