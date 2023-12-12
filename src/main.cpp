#include "../Map/GeoMap.hpp"
#include "../Map/Location.hpp"
#include "../Map/Path.hpp"
#include <iostream>

int main() {
  GeoMap map;
  map[{{100.1,100.0},"Parker Swanton"}];
  map[{{100.1,100.2},"Harry Potter"}];
  map[{{99.5,120.0},"Travis Kelce"}];
  map[{{100.2,100.2},"Luke Nelson"}];
  
  map.addPath(map[{100.1,100.2}],Location("e",100.2,100.2),Paved,"name2");
  map.addPath(Location("Green grass",0.5,0.6),Location("Blue sky",100.1,100.1),Gravel,"name",true);
  map.addPath(Location("Canton",50.5,40.4),Location("Plymouth",60.6,70.7),Dirt,"Canton Center btwn Plymouth and Canton",true);
  cout << "Done";
}