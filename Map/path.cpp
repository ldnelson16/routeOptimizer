#include "Path.hpp"
#include "Location.hpp"

Path::Path(string name_in, TerrainType ter_in, Location loc_a, Location loc_b): pathname(name_in), terrain(ter_in), vertices(std::make_pair(loc_a,loc_b)) {}

string Path::str(bool concise) const {
  if (concise) {
    return pathname + ", " + vertices.first.str(true)+"<->"+vertices.second.str(true);
  }
  else {
    return "Name: "+pathname+"\nFrom "+vertices.first.str(true)+" to "+vertices.second.str(true)+"\nWith terrain type of "+to_string(terrain);
  }
}