#include "Stack.hpp"
#include "image.h"
#include "Location.hpp"

#ifndef _REGION_GROWER_HPP_
#define _REGION_GROWER_HPP_

class RegionGrower
{
private:
  Stack<Location> locs; //Stack of locations of pixels to change
  std::string imgFile; //input file
  Location seed; //first location
  Pixel replacement; //rgba replacement
  std::string outputFile; //outputfile
  Image<Pixel> pic; //original image
public:
  RegionGrower(std::string outputFile);
  bool SetImage(std::string imgFile);
  bool SetSeed(int seedRow, int seedColumn);
  bool SetReplacement(int r, int g, int b, int a);
  void Update();
  bool GetOutput();
};

#endif
