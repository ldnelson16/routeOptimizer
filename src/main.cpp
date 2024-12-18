#include "../Map/GeoMap.hpp"
#include "../Map/Coordinates.hpp"
#include <iostream>

int main() {
  GeoMap map;
  map[{Coordinates(42.733,-84.555,"Michigan"),Coordinates(39.961,-82.999,"Ohio"),{"I-75",Paved,254*1609.34}}];

  map[{Coordinates(42.733,-84.555),Coordinates(43.074,-89.384,"Wisconsin"),{"US-23",Paved,369*1609.34}}];

  map[{Coordinates(42.733,-84.555),Coordinates(39.768,-86.163,"Indiana"),{"I94",Unknown,255*1609.34}}];

  map[{Coordinates(39.961,-82.999),Coordinates(40.264,-76.884,"Pennsylvania"),{"Canton Center",Dirt,368*1609.34}}];

  map[{Coordinates(39.961,-82.999),Coordinates(38.336,-81.612,"West Virginia"),{"Canton Center",Dirt,161*1609.34}}];

  map[{Coordinates(40.264,-76.884),Coordinates(38.336,-81.612),{"Canton Center",Dirt,366*1609.34}}];

  map[{Coordinates(39.961,-82.999),Coordinates(38.187,-84.875,"Kentucky"),{"Canton Center",Dirt,186*1609.34}}];

  map[{Coordinates(39.768,-86.163),Coordinates(38.187,-84.875),{"Canton Center",Dirt,165*1609.34}}];

  map[{Coordinates(39.798,-89.654,"Illinois"),Coordinates(38.187,-84.875),{"Canton Center",Dirt,374*1609.34}}];

  map[{Coordinates(39.798,-89.654),Coordinates(41.591,-93.604,"Iowa"),{"Canton Center",Dirt,338*1609.34}}];
  
  map[{Coordinates(40.264,-76.884),Coordinates(38.187,-84.875),{"Canton Center",Dirt,197*1609.34}}];

  map[{Coordinates(39.961,-82.999),Coordinates(39.768,-86.163),{"Canton Center",Dirt,176*1609.34}}];

  map[{Coordinates(43.074,-89.384),Coordinates(44.955,-93.102,"Minnesota"),{"Canton Center",Dirt,262*1609.34}}];

  map[{Coordinates(43.074,-89.384),Coordinates(39.798,-89.654),{"Canton Center",Dirt,264*1609.34}}];

  map[{Coordinates(43.074,-89.384),Coordinates(41.591,-93.604),{"Canton Center",Dirt,293*1609.34}}];

  map[{Coordinates(39.768,-86.163),Coordinates(39.798,-89.654),{"Canton Center",Dirt,213*1609.34}}];

  map[{Coordinates(41.591,-93.604),Coordinates(44.955,-93.102),{"Canton Center",Dirt,248*1609.34}}];
  
  Route* r1 = map(Coordinates(42.733,-84.555),Coordinates(41.591,-93.604));
  Route* r2 = map(Coordinates(38.336,-81.612),Coordinates(44.955,-93.102));

  cout << *r1 << *r2;

  cout << "Done" << endl;
}