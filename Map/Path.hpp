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
// Constructor: {string Name, double Latitude, double Longitude}
class Path {
  using vertices = pair<Location*,Location*>;
  public:
    string pathname; // Name of path (i.e. Sheldon Road)
    TerrainType terrain; // Type of terrain (i.e. Grass) (represented by enum TerrainType)
    vertices startendpair;
    // Safety level, frequency and other variables

    Path(string name_in, TerrainType ter_in, Location loc_a, Location loc_b);

    string str(bool concise=false) const;

    bool operator==(const Path& other) {
      return (*(startendpair.first)==*(other.startendpair.first)&&*(startendpair.second)==*(other.startendpair.second))||(*(startendpair.first)==*(other.startendpair.second)&&*(startendpair.second)==*(other.startendpair.first));
    }
};

#endif // PATH_HPP