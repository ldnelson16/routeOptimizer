#include "../Map/GeoMap.hpp"
#include "../Map/Coordinates.hpp"
#include <iostream>

int main() {
  GeoMap map;
  map[{"Detroit",Coordinates(4,8)}];
  map[{"Lansing",Coordinates(12,8)}];
  map[{"Ann Arbor",Coordinates(10,8)}];
  map[{"Pontiac",Coordinates(4,80)}];
  
  map[{Coordinates(4,8),Coordinates(12,8),{"Grand River",Paved}}];
  map[{Coordinates(4,80,"Toledo"),Coordinates(12,10,"Columbus"),{"US-23",Paved}}];
  map[{Coordinates(14,8,"Chicago"),Coordinates(120,8,"Grand Valley State"),{"M18",Gravel}}];
  map[{Coordinates(4,80),Coordinates(12,9),{"I94",Unknown}}];
  map[{Coordinates(50,50,"Canton"),Coordinates(60,60,"Plymouth"),{"Canton Center",Dirt}}];
  map[{Coordinates(42.281099,-83.512126),Coordinates(42.377054,-83.472391),{"drive to P's house",Paved}}];
  cout << "Done";
}