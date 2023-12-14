#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <utility>

using namespace std;

class Coordinates {
  private: 
    pair<pair<int,int>,pair<int,int>> coords;
    string name;
  public: 
    Coordinates(double lat, double lon) {
      coords = {{static_cast<int>(lat),static_cast<int>(round((lat-static_cast<int>(lat)) * 1e7))},{static_cast<int>(lon),static_cast<int>(round((lon-static_cast<int>(lon)) * 1e7))}};
    }
    Coordinates(const pair<double,double> &latlon) {
      coords = {{static_cast<int>(latlon.first),static_cast<int>(round((latlon.first-static_cast<int>(latlon.first)) * 1e7))},{static_cast<int>(latlon.second),static_cast<int>(round((latlon.second-static_cast<int>(latlon.second)) * 1e7))}};
    }
    Coordinates(int lat_big, int lat_small, int lon_big, int lon_small): coords({{lat_big,lat_small},{lon_big,lon_small}}) {}
    Coordinates(double lat, double lon, string name_in): name(name_in) {
      coords = {{static_cast<int>(lat),static_cast<int>(round((lat-static_cast<int>(lat)) * 1e7))},{static_cast<int>(lon),static_cast<int>(round((lon-static_cast<int>(lon)) * 1e7))}};
    }
    Coordinates(const pair<double,double> &latlon, string name_in): name(name_in) {
      coords = {{static_cast<int>(latlon.first),static_cast<int>(round((latlon.first-static_cast<int>(latlon.first)) * 1e7))},{static_cast<int>(latlon.second),static_cast<int>(round((latlon.second-static_cast<int>(latlon.second)) * 1e7))}};
    }
    Coordinates(int lat_big, int lat_small, int lon_big, int lon_small, string name_in): coords({{lat_big,lat_small},{lon_big,lon_small}}), name(name_in) {}

    string getName() const {return name;}

    bool operator==(const Coordinates &other) const {
      return coords==other.coords;
    }
    bool operator!=(const Coordinates &other) const {
      return !(coords==other.coords);
    }
    bool operator<(const Coordinates &other) const {
      return tie(coords) < tie(other.coords);
    }
    string operator*() const {
      return to_string(coords.first.first) + "." + to_string(coords.first.second)+","+to_string(coords.second.first) + "." + to_string(coords.second.second);
    }
};

#endif // COORDINATES_HPP