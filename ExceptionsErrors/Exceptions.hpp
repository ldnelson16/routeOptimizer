#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <cmath>
#include <string>

struct Location;

class LocationAlreadyExists: public std::exception {
  private: 
    std::string errorMessage;
  public:
    LocationAlreadyExists(Location loc); 
    
    const char* what() const noexcept override {
      return errorMessage.c_str();
    }
};

#endif // EXCEPTIONS_HPP