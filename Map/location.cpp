#include "Location.hpp"
#include "Path.hpp"

using namespace std;

std::string Location::str(bool concise) const {
  if (concise) {
    return "Name: "+name+"("+to_string(id)+")";
  }
  else {
    ostringstream loc_info;
    loc_info << "Name: "<<name<<"\n(Lat,Lon): "<<to_string(coords.first.first)<<"."<<to_string(coords.first.second)<<","<<to_string(coords.second.first)<<"."<<to_string(coords.second.second)<<")\nPaths: ";
    for (Path path: paths) {
      loc_info << path.str(concise=true) << ", ";
    }
    loc_info << "\n";
    return loc_info.str();
  }
}

Path& Location::operator[](const pair<Location,pair<TerrainType,string>> &other) const {
  for (Path& path: paths) {
    if (path==make_pair(*this,other.first)) {
      // rename path for this node
      path.terrain = other.second.first;
      path.pathname = other.second.second;
      // rename path for other node
      for (Path& otherpath: other.first.paths) {
        if (otherpath==path) {
          otherpath.terrain = other.second.first;
          otherpath.pathname = other.second.second;
        }
      }
      return path;
    }
  }
  paths.push_back(Path(other.second.second,other.second.first,this,&other.first));
  other.first.paths.push_back(Path(other.second.second,other.second.first,&(other.first),this));
  return (*this)[other];
}