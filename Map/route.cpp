#include "Route.hpp"
#include "Location.hpp"
#include "Path.hpp"

bool Route::inRoute(Location* loc) {
  for (int i=0;i<paths.size();++i) {
    if (paths[i]->start==loc || paths[i]->dest==loc) {
      return true;
    }
  }
  return false;
}