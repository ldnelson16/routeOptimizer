#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include "../ExceptionsErrors/Exceptions.hpp"

using namespace std;

// FORWARD DECLARATIONS
struct Path;
struct Location;

/* 
Creator: Luke Nelson
Start Date: 12/10/2023
*/

// Variable to represent type of terrain
enum TerrainType { 
    Paved,
    Gravel,
    Dirt,
    Grass
};

// location for Struct (node)
// Constructor: {string Name, double Latitude, double Longitude}
struct Location { 
  size_t id; // id of Location, used in storage map
  string name; // Name of location (i.e. corner of Geddes and Oxford)
  double latitude; // Latitude
  double longitude; // Longitude
  list<Path> paths; // List of paths connected to point

  Location() = default; // DEFAULT CONSTRUCTOR 
  Location(string name_in, double lat_in, double lon_in): id(0), name(name_in), latitude(lat_in), longitude(lon_in) {}

  bool operator==(const Location& other) const {
    return latitude == other.latitude && longitude == other.longitude;
  }
  bool operator<(const Location& other) const {
    return std::tie(latitude, longitude) < std::tie(other.latitude, other.longitude);
  }
};

// Path representing a connection between two locations
// Constructor: {string Name, double Latitude, double Longitude}
struct Path {
  string pathname; // Name of path (i.e. Sheldon Road)
  TerrainType terrain; // Type of terrain (i.e. Grass) (represented by enum TerrainType)
  pair<Location,Location> vertices;
  // Safety level, frequency and other variables

  Path(string name_in, TerrainType ter_in, Location loc_a, Location loc_b): pathname(name_in), terrain(ter_in), vertices({loc_a,loc_b}) {}
};

class Map {
  private:
    vector<Location> nodes;
  public:
    // Default constructor (takes no inputs)
    Map() {}

    // Add Location node
    void addLocation(Location loc) {
      if (binary_search(nodes.begin(),nodes.end(),loc)) {throw LocationAlreadyExists(loc);}
      else {
        auto insertionPoint = lower_bound(nodes.begin(), nodes.end(), loc);
        nodes.insert(insertionPoint,loc);
      }
    }

    // Add Path btwn two Location nodes
    void addPath(Location loc_a, Location loc_b, TerrainType terrain, string name) {
      
    }

    // Add Path btwn two Location nodes
    void addPath(Path path) {

    }
};

#endif // MAP_HPP