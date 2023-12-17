#include "Route.hpp"
#include "Location.hpp"
#include "Path.hpp"

bool Route::inRoute(Location* loc) const {
  for (int i=0;i<paths.size();++i) {
    if (paths[i]->start==loc || paths[i]->dest==loc) {
      return true;
    }
  }
  return false;
}

NoRouteExists::NoRouteExists(Location* start, Location* end) {
  errorMessage = "No path from " + start->str(true) + " to " + end->str(true) + ".\n";
}

Route::Route (vector<Path*> paths_in): paths(paths_in) {
  distance = 0;
  for (auto path_ptr: paths_in) {
    distance+=path_ptr->distance;
  }
}

bool Route::contains(Location* loc) const {
  for (auto path_ptr: paths) {
    if (path_ptr->dest==loc || path_ptr->start==loc) {
      return true;
    }
  }
  return false;
}