#ifndef GEOMAP_HPP
#define GEOMAP_HPP

#include <tuple>
#include <set>
#include <map>

#include "Location.hpp"
#include "Path.hpp"
#include "Coordinates.hpp"
#include "TerrainType.hpp"
#include "Route.hpp"

using namespace std;

/* 
Creator: Luke Nelson
Start Date: 12/10/2023
*/

class GeoMap {
  using coordinates = pair<pair<int,int>,pair<int,int>>;
  private:
    set<Location*> firstlocs;
    map<Coordinates,Location*> locations;
  public:
    friend class LocationDoesntExist;
    friend class PathAlreadyExists;
    friend class LocationAlreadyExists;
    // EXCEPTIONS (PRIVATE TO GEOMAP)

    // Default constructor (takes no inputs)
    GeoMap() {}

    // CONTAINS
    // RETURNS TRUE IF LOCATION WITH SPECIFIC COORDINATES EXISTS IN GEOMAP
    bool contains(const Coordinates &coords) {
      return locations.find(coords)!=locations.end();
    }

    // [] operator 
    // RETURNS POINTER TO LOCATION INSERTED (OR EXISTING LOCATION IF IT ALREADY EXISTS)
    // INSERT BY ADDING A TUPLE WITH {NAME,COORDS}
    Location* operator[](const tuple<string,Coordinates>& loc_info) {
      // check for existing location
      auto it = locations.find(get<1>(loc_info));
      if (it!=locations.end()) {return (*it).second;}
      // create location
      Location* loc = new Location(get<0>(loc_info),get<1>(loc_info));
      // add to first locations and locations map
      firstlocs.insert(loc);
      locations[get<1>(loc_info)] = loc;
      // return pointer to inserted location
      return loc;
    }

    // [] operator 
    // RETURNS POINTER TO LOCATION INSERTED (OR EXISTING LOCATION IF IT ALREADY EXISTS)
    // INSERT BY ADDING COORDS (IF DOESN'T EXIST ADDS NAME AS COORDINATES)
    Location* operator[](const Coordinates& coords) {
      // check for existing location
      auto it = locations.find(coords);
      if (it!=locations.end()) {return (*it).second;}
      // create location
      Location* loc = new Location(*coords,coords);
      // add to first locations and locations map
      firstlocs.insert(loc);
      locations[coords] = loc;
      // return pointer to inserted location
      return loc;
    }

    // [] operator
    // RETURNS POINTER TO PATH OBJECT (OR EXISTING LOCATION IF IT ALREADY EXISTS)
    // INSERT BY ADDING A PAIR WITH TWO TUPLES AS FOLLOWS: {NAME,COORDS}
    Path* operator[](const tuple<Coordinates,Coordinates,tuple<string,TerrainType>>& locs_info) {
      // check for locations
      auto it1 = locations.find(get<0>(locs_info));
      auto it2 = locations.find(get<1>(locs_info));
      if (it1!=locations.end()&&it2!=locations.end()) { // both locations exist
        // check for existence in first locations
        auto it1a = firstlocs.find(it1->second);
        auto it2a = firstlocs.find(it2->second);
        // both locations exists, modify path
        if (get<0>(locs_info).getName()!="") {it1->second->setName(get<0>(locs_info).getName());}
        if (get<1>(locs_info).getName()!="") {it2->second->setName(get<1>(locs_info).getName());}
        if (it1a!=firstlocs.end()&&it2a!=firstlocs.end()) {
          // both locations are in firstlocs (one must be removed)
          firstlocs.erase(it2a); // arbitarily remove 2
          return (it1->second)->operator()(it2->second,get<0>(get<2>(locs_info)),get<1>(get<2>(locs_info)));
        }
        else if (it1a!=firstlocs.end()) {
          // only 1 is in firstlocs (remove 1 from firstlocs)
          firstlocs.erase(it1a);
          return (it1->second)->operator()(it2->second,get<0>(get<2>(locs_info)),get<1>(get<2>(locs_info)));
        }
        else if (it2a!=firstlocs.end()) {
          // only 2 is in firstlocs (remove 2 from firstlocs)
          firstlocs.erase(it2a); 
          return (it1->second)->operator()(it2->second,get<0>(get<2>(locs_info)),get<1>(get<2>(locs_info)));
        }
        else {
          // no locations in firstlocs
          return (it1->second)->operator()(it2->second,get<0>(get<2>(locs_info)),get<1>(get<2>(locs_info)));
        }
      }
      else if (it1!=locations.end()) { // only location 1 exists
        if (get<0>(locs_info).getName()!="") {it1->second->setName(get<0>(locs_info).getName());}
        // create location 2
        Location* loc = new Location(get<1>(locs_info).getName()=="" ? *get<1>(locs_info):get<1>(locs_info).getName(),get<1>(locs_info)); 
        locations[get<1>(locs_info)] = loc;
        // create path btwn loc 1 and loc 2 (hence why no adding to firstlocs)
        return (it1->second)->operator()(loc,get<0>(get<2>(locs_info)),get<1>(get<2>(locs_info)));
      }
      else if (it2!=locations.end()) { // only location 2 exists
        if (get<1>(locs_info).getName()!="") {it2->second->setName(get<1>(locs_info).getName());}
        // create location 1
        Location* loc = new Location(get<0>(locs_info).getName()=="" ? *get<0>(locs_info):get<0>(locs_info).getName(),get<0>(locs_info));
        locations[get<0>(locs_info)] = loc;
        // create path btwn loc 1 and loc 2 (hence why no adding to firstlocs)
        return loc->operator()(it2->second,get<0>(get<2>(locs_info)),get<1>(get<2>(locs_info)));
      }
      else { // neither location exists
        // create locations 1 and 2
        Location* loc1 = new Location(get<0>(locs_info).getName()=="" ? *get<0>(locs_info):get<0>(locs_info).getName(),get<0>(locs_info)); // 1
        locations[get<0>(locs_info)] = loc1;
        Location* loc2 = new Location(get<1>(locs_info).getName()=="" ? *get<1>(locs_info):get<1>(locs_info).getName(),get<1>(locs_info)); // 2
        locations[get<1>(locs_info)] = loc2;
        firstlocs.insert(loc1);
        // create path between new locations
        return loc1->operator()(loc2,get<0>(get<2>(locs_info)),get<1>(get<2>(locs_info)));
      }
      return nullptr;
    }

    Route& findPath(const Route& route, Location* begin, Location* end) {
      vector<pair<Location*,double>> options = begin->getOptions(route,end);
    }
};

#endif // GEOMAP_HPP