#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <sstream>

#include "Location.hpp"
#include "Path.hpp"

using namespace std;

// FORWARD DECLARATIONS
enum TerrainType;
class Path;
class Location;
class LocationAlreadyExists;
class PathAlreadyExists;

/* 
Creator: Luke Nelson
Start Date: 12/10/2023
*/

class Map {
  private:
    vector<Location> nodes;
  public:
    friend class LocationDoesntExist;
    friend class PathAlreadyExists;
    friend class LocationAlreadyExists;
    // EXCEPTIONS (PRIVATE TO MAP)
    class LocationAlreadyExists: public std::exception {
    private: 
      string errorMessage;
    public:
      LocationAlreadyExists(const Location &loc) {
        errorMessage = "Location already exists.\n"+loc.str();
      }
      
      const char* what() const noexcept override {
        return errorMessage.c_str();
      }
    };
    class PathAlreadyExists: public std::exception {
      private: 
        string errorMessage;
      public:
        PathAlreadyExists(const Path &p) {
          errorMessage = "Path already exists.\n"+p.str();
        } 
        const char* what() const noexcept override {
          return errorMessage.c_str();
        }
    };
    class LocationDoesntExist: public std::exception {
      private: 
        string errorMessage;
      public:
        LocationDoesntExist(const vector<Location>& locs) {
          errorMessage = "The following location(s) aren't in the map yet:\n";
          ostringstream message;
          for (const Location& loc: locs) {
            message << loc.str();
          }
          errorMessage+=message.str();
        } 
        const char* what() const noexcept override {
          return errorMessage.c_str();
        }
    };
    // Default constructor (takes no inputs)
    Map() {}

    // Add Location node
    void addLocation(const Location &loc) {
      if (binary_search(nodes.begin(),nodes.end(),loc)) {throw LocationAlreadyExists(loc);}
      else {
        auto insertionPoint = lower_bound(nodes.begin(), nodes.end(), loc);
        nodes.insert(insertionPoint,loc);
      }
    }

    // Add Path btwn two Location nodes
    void addPath(const Location &loc_a, const Location &loc_b, TerrainType terrain, string name) {
      auto ita = lower_bound(nodes.begin(),nodes.end(),loc_a);
      auto itb = lower_bound(nodes.begin(),nodes.end(),loc_b);
      // both locations exist
      if (ita!=nodes.end() && itb!=nodes.end() && *ita==loc_a && *itb==loc_b) {
        // path already exists
        for (auto &it: ita->paths) {
          if (it==Path(name,terrain,loc_a,loc_b)) {
            throw PathAlreadyExists(Path(name,terrain,loc_a,loc_b));
          }
        }
        //path doesnt exist
        (*ita).paths.push_back(Path(name,terrain,loc_a,loc_b));
        (*itb).paths.push_back(Path(name,terrain,loc_b,loc_a));
      }
      // one or neither locations exist
      else {
        if ((ita==nodes.end()||*ita!=loc_a)&&(itb==nodes.end()||*ita!=loc_b)) {
          throw LocationDoesntExist({loc_a,loc_b});
        }
        else if (ita==nodes.end()||*ita!=loc_a) {
          throw LocationDoesntExist({loc_a});
        }
        else {
          throw LocationDoesntExist({loc_b});
        }
      }
    }

    // Add Path btwn two Location nodes
    void addPath(const Path &path) {
      auto ita = lower_bound(nodes.begin(),nodes.end(),*(path.startendpair.first));
      auto itb = lower_bound(nodes.begin(),nodes.end(),*(path.startendpair.second));
      // both locations exist
      if (ita!=nodes.end() && itb!=nodes.end() && *ita==*(path.startendpair.first) && *itb==*(path.startendpair.second)) {
        // path already exists
        for (auto &it: ita->paths) {
          if (it==path) {
            throw PathAlreadyExists(path);
          }
        }
        //path doesnt exist
        (*ita).paths.push_back(path);
        (*itb).paths.push_back(Path(path));
      }
      // one or neither locations exist
      else {
        if ((ita==nodes.end()||*ita!=*(path.startendpair.first))&&(itb==nodes.end()||*ita!=*(path.startendpair.second))) {
          throw LocationDoesntExist({*(path.startendpair.first),*(path.startendpair.second)});
        }
        else if (ita==nodes.end()||*ita!=*(path.startendpair.first)) {
          throw LocationDoesntExist({*(path.startendpair.first)});
        }
        else {
          throw LocationDoesntExist({*(path.startendpair.second)});
        }
      }
    }
};

#endif // MAP_HPP