#include "Exceptions.hpp"
#include "../Map/Location.hpp"
#include "../Map/Path.hpp"

LocationAlreadyExists::LocationAlreadyExists(Location loc) {
  errorMessage = "Location already exists.\n"+loc.str();
}

PathAlreadyExists::PathAlreadyExists(Path p) {
  errorMessage = "Path already exists.\n"+p.str();
}

LocationDoesntExist::LocationDoesntExist(Location a, Location b) {
  errorMessage = "The following location(s) isn't in the map yet.";
}