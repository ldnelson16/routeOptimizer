#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <sstream>

#include "Location.hpp"
#include "Path.hpp"
#include "../ExceptionsErrors/Exceptions.hpp"

using namespace std;

// FORWARD DECLARATIONS
enum TerrainType;
class Path;
class Location;
class LocationAlreadyExists;
class PathAlreadyExists;

/* 
Creator: Luke Nelson
Start Date: 12/10/2023
*/

class Map {
  private:
    vector<Location> nodes;
  public:
    // Default constructor (takes no inputs)
    Map() {}

    // Add Location node
    void addLocation(const Location &loc) {
      if (binary_search(nodes.begin(),nodes.end(),loc)) {throw LocationAlreadyExists(loc);}
      else {
        auto insertionPoint = lower_bound(nodes.begin(), nodes.end(), loc);
        nodes.insert(insertionPoint,loc);
      }
    }

    // Add Path btwn two Location nodes
    void addPath(const Location &loc_a, const Location &loc_b, TerrainType terrain, string name) {
      /*for (Path path: loc_a.paths) {
        if (path==Path(name,terrain,loc_a,loc_b)) {throw PathAlreadyExists(Path(name,terrain,loc_a,loc_b));}
      }*/
      auto ita = lower_bound(nodes.begin(),nodes.end(),loc_a);
      auto itb = lower_bound(nodes.begin(),nodes.end(),loc_b);
      // both locations exist
      if (ita!=nodes.end() && itb!=nodes.end() && (*ita).coords==loc_a.coords && (*itb).coords==loc_b.coords) {
        // path already exists
        (*ita).paths.push_back(Path(name,terrain,loc_a,loc_b));
        (*itb).paths.push_back(Path(name,terrain,loc_b,loc_a));
        //path doesnt exist
      }
      // one or neither locations exist
      else {
        throw LocationDoesntExist(loc_a, loc_b);
      }
    }

    // Add Path btwn two Location nodes
    void addPath(Path &path) {
      (path.vertices.first.paths).push_back(path);
      (path.vertices.second.paths).push_back(path);
    }
};

#endif // MAP_HPP