#include <iostream>
#include "region_grower.hpp"

using std::endl;

int main( int argc, char* argv[] )
{
  if (argc != 8) //8 arguments
  {
    std::cout << "Error Usage: Input File, SeedX, SeedY, R, G, B, Output File";
    return EXIT_FAILURE;
  }
  else
  {
    int row, column, red, g, b, a;
    std::string input = argv[1];
    try
    {
      red = std::stoi(argv[4]);
    }
    catch (std::invalid_argument e) //stoi throws invalid_argument when a type other than string comes in
    {
      std::cout << "Error Bad Argument.\n";
      return EXIT_FAILURE;
    }
    try
    {
      g = std::stoi(argv[5]);
    }
    catch (std::invalid_argument e)
    {
      std::cout << "Error Bad Argument.\n";
      return EXIT_FAILURE;
    }
    try
    {
      b = std::stoi(argv[6]);
    }
    catch (std::invalid_argument e)
    {
      std::cout << "Error Bad Argument.\n";
      return EXIT_FAILURE;
    }
    a = 255; //alpha is always 255 and is not a parameter, I thought it was so I hardcoded it in
    try
    {
      row = std::stoi(argv[2]);
    }
    catch (std::invalid_argument e)
    {
      std::cout << "Error Bad Argument.\n";
      return EXIT_FAILURE;
    }
    try
    {
      column = std::stoi(argv[3]);
    }
    catch (std::invalid_argument e)
    {
      std::cout << "Error Bad Argument.\n";
      return EXIT_FAILURE;
    }
    RegionGrower r(argv[7]); //Passes output file as a string to RegionGrower constructor
    //If any of the functions return false, it means they caught an exception in the class definition, so the program should fail
    bool setImage = r.SetImage(argv[1]);
    if (!setImage)
    {
      std::cout << "Error Bad File.\n";
      return EXIT_FAILURE;
    }
    bool seed = r.SetSeed(row, column);
    if (!seed)
    {
      std::cout << "Error Invalid Seed Values.\n";
      return EXIT_FAILURE;
    }
    bool replacement = r.SetReplacement(red, g, b, a);
    if (!replacement)
    {
      std::cout << "Error Invalid Replacement Color.\n";
      return EXIT_FAILURE;
    }
    bool output = r.GetOutput();
    if (!output)
    {
      std::cout << "Error Could Not Print to Output File.\n";
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
}
