#include "Path.hpp"
#include "Location.hpp"

Path::Path(string name_in, TerrainType ter_in, Location* loc_a, Location* loc_b): pathname(name_in), terrain(ter_in), start(loc_a), dest(loc_b) {}

Path::Path(const Path& other): pathname(other.pathname), terrain(other.terrain), start(other.start), dest(other.dest) {}

Path::Path(const Path& other, bool reverse): pathname(other.pathname), terrain(other.terrain){
  if (reverse) {start = other.dest; dest = other.start;}
  else {start = other.start; dest = other.dest;}
}

string Path::str(bool concise) const {
  if (concise) {
    return pathname + ", " + start->str(true)+"<->"+dest->str(true);
  }
  else {
    return "Name: "+pathname+"\nFrom "+start->str(true)+" to "+dest->str(true)+"\nWith terrain type of "+to_string(terrain);
  }
}