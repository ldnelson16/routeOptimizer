#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <vector>
#include <sstream>

#include "TerrainType.hpp"
#include "Coordinates.hpp"

using namespace std;

// FORWARD DECLARATION
class GeoMap;
class Path;
class Route;

// location for Struct (node)
// Constructor: {string Name, double Latitude, double Longitude}
class Location { 
  friend class Path;
  friend class GeoMap;
  friend class CompareLocations;
  friend class Route;
  private: 
    string name; // Name of location (i.e. corner of Geddes and Oxford)
    Coordinates coords; // {latitude,longitude} (pair<pair<int,int>,pair<int,int>>)
    vector<Path> paths; // List of paths connected to point
  public:
    // DEFAULT CONSTRUCTOR 
    Location() = default;
    // Complete CTOR
    Location(string name_in, Coordinates coords_in): name(name_in), coords(coords_in) {}

    bool operator==(const Location& other) const {
      return coords==other.coords;
    }
    bool operator!=(const Location& other) const {
      return coords!=other.coords;
    }
    bool operator<(const Location& other) const {
      return coords < other.coords;
    }
    // RETURNS TRUE IF LOCATION HAS PATH TO POINTED TO LOCATION
    bool has(Location* other) const;
    // RETURNS TRUE IF LOCATION HAS PATH TO COORDS
    bool goesTo(Coordinates coords) const;
    void setName(string name_in) {name = name_in;}
    vector<pair<Path*,double>> getOptions(Route route, Location* dest);
    Path* operator[](Location* other) {return this->operator()(other);}
    Path* operator()(Location* other, string name="", TerrainType terrain = Unknown, double distance = -1., bool modify = true);
    string str(bool concise = false) const;
};

class CompareLocations{
  private:
    Location* final;
  public: 
    CompareLocations(Location* final_in): final(final_in) {}
    bool operator()(const Route& lhs, const Route& rhs) const;
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
    LocationDoesntExist(const vector<Coordinates>& coordsset) {
      errorMessage = "The following location(s) aren't in the geomap yet:\n";
      ostringstream message;
      for (const Coordinates& coords: coordsset) {
        message << *coords;
      }
      errorMessage+=message.str();
    } 
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

#endif // LOCATION_HPP