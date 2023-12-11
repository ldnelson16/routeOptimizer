#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <cmath>

using namespace std;

// FORWARD DECLARATION
class Path;

// location for Struct (node)
// Constructor: {string Name, double Latitude, double Longitude}
class Location { 
  using coordinates = pair<pair<int,int>,pair<int,int>>;
  public:
    size_t id; // id of Location, used in storage map
    string name; // Name of location (i.e. corner of Geddes and Oxford)
    coordinates coords; // {latitude,longitude} (pair)
    mutable list<Path> paths; // List of paths connected to point

    Location() = default; // DEFAULT CONSTRUCTOR 
    Location(string name_in, double lat_in, double lon_in): id(0), name(name_in) {
      coords = {{static_cast<int>(lat_in),static_cast<int>(round((lat_in-static_cast<int>(lat_in)) * 1e6))},{static_cast<int>(lon_in),static_cast<int>(round((lon_in-static_cast<int>(lon_in)) * 1e6))}};
    }

    bool operator==(const Location& other) const {
      return coords==other.coords;
    }
    bool operator<(const Location& other) const {
      return tie(coords) < tie(other.coords);
    }
    string str(bool concise = false) const;
};

#endif // LOCATION_HPP