//Program RegionGrower: Colors a continuous region of pixels defined by a pixel, similar to paint bucket tool

//Programmer: Brady Siegel

//I didn't cheat (I never received nor gave unauthorized assistance on this project)


#include "region_grower.hpp"
#include "lodepng.h"

RegionGrower::RegionGrower(std::string outputFile)
{
  this->outputFile = outputFile;
}
bool RegionGrower::SetImage(std::string imgFile)
{
  try
  {
    this->imgFile = imgFile;
    pic = readFromFile(imgFile);
  } catch (std::runtime_error e) //Throws when readFromFile breaks
  {
    return false;
  }
  return true;
}
bool RegionGrower::SetSeed(int seedRow, int seedColumn)
{
  if (seedRow < 0 || seedRow > pic.height() || seedColumn < 0 || seedColumn > pic.width()) //range restrictions
  {
    return false;
  }
  else
  {
    seed.seedRow = seedRow;
    seed.seedColumn = seedColumn;
  }
  return true;
}
bool RegionGrower::SetReplacement(int r, int g, int b, int a)
{
  if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 || a < 0 || a > 255) //range restrictions
  {
    return false;
  }
  replacement.red = r;
  replacement.blue = b;
  replacement.green = g;
  replacement.alpha = a;
  return true;
}
void RegionGrower::Update()
{
  //update algorithm specified in the project reqs
  locs.push(seed); //makes locs not empty before starting while
  bool pushit = false; //flag to tell the program to push a Location to the stack
  while (!locs.isEmpty())
  {
    Location currentLocation = locs.peek();
    locs.pop();
    Location next;
    for (int c = 0; c < 4; c++) //4 directions
    {
      pushit = false;
      if (c == 0) //Down
      {
        next.seedRow = currentLocation.seedRow + 1;
        next.seedColumn = currentLocation.seedColumn;
        if (next.seedRow < pic.height())
        {
          pushit = true;
        }
      }
      else if (c == 1) //Up
      {
        next.seedRow = currentLocation.seedRow - 1;
        next.seedColumn = currentLocation.seedColumn;
        if (next.seedRow > 0)
        {
          pushit = true;
        }
      }
      else if (c == 2) //Right
      {
        next.seedRow = currentLocation.seedRow;
        next.seedColumn = currentLocation.seedColumn + 1;
        if (next.seedColumn < pic.width())
        {
          pushit = true;
        }
      }
      else //Left
      {
        next.seedRow = currentLocation.seedRow;
        next.seedColumn = currentLocation.seedColumn - 1;
        if (next.seedColumn > 0)
        {
          pushit = true;
        }
      }
      //Checks if pushit is true first so it doesn't check pixels outside range.
      //Then checks that the next pixel is the same as current, and that it isn't the same as the replacement
      if (pushit && pic(next.seedRow, next.seedColumn) == pic(currentLocation.seedRow, currentLocation.seedColumn) && pic(next.seedRow, next.seedColumn) != replacement)
      {
        locs.push(next);
      }
    }
    //Changes each rbga value.
    pic(currentLocation.seedRow, currentLocation.seedColumn).red = (int) replacement.red;
    pic(currentLocation.seedRow, currentLocation.seedColumn).blue = (int) replacement.blue;
    pic(currentLocation.seedRow, currentLocation.seedColumn).green = (int) replacement.green;
    pic(currentLocation.seedRow, currentLocation.seedColumn).alpha = (int) replacement.alpha;
  }
}
bool RegionGrower::GetOutput()
{
  Update(); //update image
  try
  {
    writeToFile(pic, outputFile);
    return true;
  } catch (std::runtime_error e) //Thrown if writeToFile breaks
  {
    return false;
  }
}
