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
#include "TerrainType.hpp"

using namespace std;

class Location;

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