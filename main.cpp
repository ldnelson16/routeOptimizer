#include "Map.hpp"
#include <iostream>

int main() {
  Map map;
  map.addLocation(Location("Hello",100.1,100.2));
  map.addLocation(Location("Bye",100.2,100.2));
  for (double i=0.; i < 100; i+=0.1) {
    map.addLocation(Location("Hello",100.4,i));
  }
}