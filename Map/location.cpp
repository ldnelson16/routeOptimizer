#include "Location.hpp"
#include "Path.hpp"
#include "Route.hpp"

// FORWARD DECLARATION
class GeoMap;

using namespace std;

std::string Location::str(bool concise) const {
  if (concise) {
    return "Name: "+name;
  }
  else {
    ostringstream loc_info;
    loc_info << "Name: "<<name<<"\n(Lat,Lon): "<<*coords<<")\nPaths: ";
    for (const Path& path: paths) {
      loc_info << path.str(concise=true) << ", ";
    }
    loc_info << "\n";
    return loc_info.str();
  }
}

Path* Location::operator()(Location* other, string name,TerrainType terrain,double distance, bool modify) {
  // check if path already exists
  for (int i=0;i<paths.size();++i) {
    if(paths[i].dest==other) {
      if (!modify) {throw PathAlreadyExists(paths[i]);}
      paths[i].pathname = name;
      paths[i].terrain = terrain;
      return &paths[i];
    }
  }
  // modify defaults
  if (name=="") {name=name+" to "+other->name;}
  // push into path vectors
  if (distance==-1) {
    paths.push_back(Path(name,terrain,this,other));
    other->paths.push_back(Path(name,terrain,other,this));
  }
  else {
    paths.push_back(Path(name,terrain,this,other,distance));
    other->paths.push_back(Path(name,terrain,other,this,distance));
  }
  return &paths.back();
}

bool Location::has(Location* other) const {
  for (const Path& path: paths) {
    if (path.dest==other) {return true;}
  }
  return false;
}

bool Location::goesTo(Coordinates coords) const {
  for (const Path& path: paths) {
    if (path.dest->coords==coords) {return true;}
  }
  return false;
}

vector<pair<Path*, double>> Location::getOptions(Route route, Location* dest) {
  vector<pair<Path*, double>> lst;
  // check all paths in current route
  for (int i=0;i<paths.size();++i) {
    if (!route.inRoute(paths[i].dest)) { // if not in route already, add to vector of options
      lst.push_back({&paths[i],paths[i].distance});
    }
  }
  return lst;
}

bool CompareLocations::operator()(const Route& lhs, const Route& rhs) const {
  double lhs_dist = lhs.paths.back()->dest->coords.dist(final->coords);
  double rhs_dist = rhs.paths.back()->dest->coords.dist(final->coords);
  double cost_lhs = lhs.distance+lhs_dist;
  double cost_rhs = rhs.distance+rhs_dist;
  return cost_lhs > cost_rhs;
}