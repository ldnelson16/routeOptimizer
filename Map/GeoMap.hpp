#ifndef GEOMAP_HPP
#define GEOMAP_HPP

#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <sstream>

#include "Location.hpp"
#include "Path.hpp"

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

class GeoMap {
  private:
    vector<Location> nodes;
  public:
    friend class LocationDoesntExist;
    friend class PathAlreadyExists;
    friend class LocationAlreadyExists;
    // EXCEPTIONS (PRIVATE TO GEOMAP)

    // Default constructor (takes no inputs)
    GeoMap() {}

    // [] operator (returns reference to position at that location (creates one if it doesn't exist))
    Location& operator[](pair<double,double> latlon) {
      if (!contains(latlon)) { // return doesn't already exist in geomap
        addLocation(Location("",latlon.first,latlon.second));
      }
      auto it = lower_bound(nodes.begin(),nodes.end(),Location("",latlon.first,latlon.second));
      return *it;
    }

    // [] operator (requires name) reference to position at that location (creates one if it doesn't exist)
    // Names element as well (or changes name)
    Location& operator[](pair<pair<double,double>,string> latlonname) {
      if (!contains(latlonname.first)) { // return doesn't already exist in geomap
        addLocation(Location(latlonname.second,latlonname.first.first,latlonname.first.second));
      }
      auto it = lower_bound(nodes.begin(),nodes.end(),Location("",latlonname.first.first,latlonname.first.second));
      (*it).name=latlonname.second;
      return *it;
    }

    // () operator to create a path (returns reference to that path)
    Path& operator()(Location& loc_a, Location& loc_b, TerrainType terrain, string name, bool force = true) {
      addPath(loc_a,loc_b,terrain,name,force);
      return loc_a[make_pair(loc_b,make_pair(terrain,name))];
    }

    // returns true if latlon pair is in geomap, false if not
    bool contains(pair<double,double> latlon) {
      return (binary_search(nodes.begin(),nodes.end(),Location("",latlon.first,latlon.second)));
    }

    // Add Location node
    void addLocation(const Location &loc) {
      if (binary_search(nodes.begin(),nodes.end(),loc)) {throw LocationAlreadyExists(loc);}
      else {
        auto insertionPoint = lower_bound(nodes.begin(), nodes.end(), loc);
        nodes.insert(insertionPoint,loc);
      }
    }

    // Add Path btwn two Location nodes
    void addPath(const Location &loc_a, const Location &loc_b, TerrainType terrain, string name, bool force = false) {
      auto ita = lower_bound(nodes.begin(),nodes.end(),loc_a);
      auto itb = lower_bound(nodes.begin(),nodes.end(),loc_b);
      // both locations exist
      if (ita!=nodes.end() && itb!=nodes.end() && *ita==loc_a && *itb==loc_b) {
        // path already exists
        for (auto &it: ita->paths) {
          if (it==make_pair(loc_a,loc_b)) {
            throw PathAlreadyExists(it);
          }
        }
        //path doesnt exist
        (*ita).paths.push_back(Path(name,terrain,&loc_a,&loc_b));
        (*itb).paths.push_back(Path(name,terrain,&loc_b,&loc_a));
      }
      // one or neither locations exist
      else {
        if (force) {
          if ((ita==nodes.end()||*ita!=loc_a)&&(itb==nodes.end()||*ita!=loc_b)) {
            // create two locations
            addLocation(loc_a);
            addLocation(loc_b);
          }
          else if (ita==nodes.end()||*ita!=loc_a) {
            addLocation(loc_a);
          }
          else {
            addLocation(loc_b);
          }
          loc_a.paths.push_back(Path(name,terrain,&loc_a,&loc_b));
          loc_b.paths.push_back(Path(name,terrain,&loc_b,&loc_a));
        }
        else {
          if ((ita==nodes.end()||*ita!=loc_a)&&(itb==nodes.end()||*ita!=loc_b)) {
            throw LocationDoesntExist({loc_a,loc_b});
          }
          else if (ita==nodes.end()||*ita!=loc_a) {
            throw LocationDoesntExist({loc_a});
          }
          else {
            throw LocationDoesntExist({loc_b});
          }
        }
      }
    }
};

#endif // GEOMAP_HPP