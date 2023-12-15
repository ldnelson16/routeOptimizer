#include "Location.hpp"
#include "Path.hpp"
#include "Route.hpp"

// FORWARD DECLARATION
class GeoMap;

using namespace std;

std::string Location::str(bool concise) const {
  if (concise) {
    return "Name: "+name+"\n";
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

Path* Location::operator()(Location* other, string name,TerrainType terrain,bool modify) {
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
  // Create path and use copy ctor for other
  Path forward(name,terrain,this,other);
  // push into path vectors
  paths.push_back(Path(name,terrain,this,other));
  other->paths.push_back(Path(name,terrain,other,this));
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

vector<pair<Location*, double>> Location::getOptions(Route* route, Location* dest) {
  vector<pair<Location*, double>> lst;
  // check all paths in current route
  for (const Path& p: paths) {
    if (!route->inRoute(p.dest)) { // if not in route already, add to vector of options
      lst.push_back({p.dest,p.distance});
    }
  }
  return lst;
}