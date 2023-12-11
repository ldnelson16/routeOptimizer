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