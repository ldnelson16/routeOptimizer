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

#include "TerrainType.hpp"

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
    // Complete CTOR
    Location(string name_in, double lat_in, double lon_in): id(0), name(name_in) {
      coords = {{static_cast<int>(lat_in),static_cast<int>(round((lat_in-static_cast<int>(lat_in)) * 1e6))},{static_cast<int>(lon_in),static_cast<int>(round((lon_in-static_cast<int>(lon_in)) * 1e6))}};
    }

    bool operator==(const Location& other) const {
      return coords==other.coords;
    }
    bool operator!=(const Location& other) const {
      return coords!=other.coords;
    }
    bool operator<(const Location& other) const {
      return tie(coords) < tie(other.coords);
    }
    Path& operator[](const pair<Location,pair<TerrainType,string>> &other) const;
    string str(bool concise = false) const;
};

class LocationAlreadyExists: public std::exception {
private: 
  string errorMessage;
public:
  LocationAlreadyExists(const Location &loc) {
    errorMessage = "Location already exists.\n"+loc.str();
  }
  
  const char* what() const noexcept override {
    return errorMessage.c_str();
  }
};
class LocationDoesntExist: public std::exception {
  private: 
    string errorMessage;
  public:
    LocationDoesntExist(const vector<Location>& locs) {
      errorMessage = "The following location(s) aren't in the geomap yet:\n";
      ostringstream message;
      for (const Location& loc: locs) {
        message << loc.str();
      }
      errorMessage+=message.str();
    } 
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

#endif // LOCATION_HPP