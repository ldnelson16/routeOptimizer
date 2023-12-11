#include "Exceptions.hpp"
#include "Map.hpp"

LocationAlreadyExists::LocationAlreadyExists(Location loc) {
  errorMessage = "Location "+loc.name+" at (Lat,Lon) ("+to_string(round(loc.latitude*100000)/100000)+","+to_string(round(loc.longitude*100000)/100000)+")";
}