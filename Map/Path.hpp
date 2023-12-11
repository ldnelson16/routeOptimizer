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
  public:
    string pathname; // Name of path (i.e. Sheldon Road)
    TerrainType terrain; // Type of terrain (i.e. Grass) (represented by enum TerrainType)
    pair<Location,Location> vertices;
    // Safety level, frequency and other variables

    Path(string name_in, TerrainType ter_in, Location loc_a, Location loc_b);

    string str(bool concise=false) const;

    bool operator==(const Path& other) {
      return (vertices.first==other.vertices.first && vertices.second==other.vertices.second) || (vertices.second==other.vertices.first && vertices.first==other.vertices.second);
    }
};

#endif // PATH_HPP