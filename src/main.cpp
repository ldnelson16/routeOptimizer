#include "../Map/Map.hpp"
#include "../Map/Location.hpp"
#include "../Map/Path.hpp"
#include <iostream>

int main() {
  Map map;
  map.addLocation(Location("Hello",100.1,100.2));
  map.addLocation(Location("Bye",100.2,100.2));
  map.addLocation(Location("G",0.5,0.6));
  map.addPath(Location("h",100.1,100.2),Location("e",100.2,100.2),Paved,"name2");
  map.addPath(Location("Green grass",0.5,0.6),Location("Blue sky",100.1,100.2),Gravel,"name");
  cout << "Done";
}