#include "Path.hpp"
#include "Location.hpp"

Path::Path(string name_in, TerrainType ter_in, Location loc_a, Location loc_b): pathname(name_in), terrain(ter_in), startendpair({&loc_a,&loc_b}) {}

Path::Path(const Path& other): pathname(other.pathname), terrain(other.terrain), startendpair({other.startendpair.second,other.startendpair.first}) {}

string Path::str(bool concise) const {
  if (concise) {
    return pathname + ", " + startendpair.first->str(true)+"<->"+startendpair.second->str(true);
  }
  else {
    return "Name: "+pathname+"\nFrom "+startendpair.first->str(true)+" to "+startendpair.second->str(true)+"\nWith terrain type of "+to_string(terrain);
  }
}