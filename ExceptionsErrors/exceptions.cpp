#include "Exceptions.hpp"
#include "../Map/Location.hpp"
#include "../Map/Path.hpp"

LocationAlreadyExists::LocationAlreadyExists(const Location &loc) {
  errorMessage = "Location already exists.\n"+loc.str();
}

PathAlreadyExists::PathAlreadyExists(const Path &p) {
  errorMessage = "Path already exists.\n"+p.str();
}

LocationDoesntExist::LocationDoesntExist(const Location &a, const Location &b) {
  errorMessage = "The following location(s) isn't in the map yet:\n";
  ostringstream message;
  if (lower_bound(nodes.begin(),nodes.end(),a))
}