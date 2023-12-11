#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <cmath>
#include <string>

// FORWARD DECLARATIONS
class Path;
class Location;

using namespace std;

class LocationAlreadyExists: public std::exception {
  private: 
    string errorMessage;
  public:
    LocationAlreadyExists(Location loc);
    
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

class PathAlreadyExists: public std::exception {
  private: 
    string errorMessage;
  public:
    PathAlreadyExists(Path p); 
    
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

class LocationDoesntExist: public std::exception {
  private: 
    string errorMessage;
  public:
    LocationDoesntExist(Location a, Location b); 
    
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

#endif // EXCEPTIONS_HPP