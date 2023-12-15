#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <cmath>
#include <tuple>

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
    pair<double,double> toDouble() const {
      return {coords.first.first+10e-8*coords.first.second,coords.second.first+10e-8*coords.second.second};
    }
    pair<double,double> toRadians(const pair<double,double> &degrees) {
      return {degrees.first * (M_PI / 180.0),degrees.second * (M_PI / 180.0)};
    }
    static constexpr double EARTH_RADIUS = 6371000.0;  // Radius of the Earth in meters
    double dist(const Coordinates &other) {
      pair<double,double> latlon1 = toDouble();
      pair<double,double> latlon2 = other.toDouble();
      latlon1 = toRadians(toDouble());
      latlon2 = toRadians(other.toDouble());
      // Calculate differences in coordinates
      double dlat = latlon2.first - latlon1.first;
      double dlon = latlon2.second - latlon1.second;
      // Haversine formula
      double a = sin(dlat/2.0) * sin(dlat/2.0) + cos(latlon1.first) * cos(latlon2.first) * sin(dlon/2.0) * sin(dlon/2.0);
      double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
      double distance = EARTH_RADIUS * c;
      return distance;
    }
};

#endif // COORDINATES_HPP