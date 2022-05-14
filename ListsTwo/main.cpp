#include <iostream>
#include <fstream>
#include "CommandExecutor.h"
#include "BidirectionalList.h"

using namespace bavykin;

const int ARGUMENT_COUNT_REQUIRED = 2;

int main(int argc, char* argv[])
{
  /*list< int > blah;
  blah.pushBack(2);
  list< int > blah2;
  blah2 = blah;
  blah.clear();
  std::cout << blah2 << std::endl;*/

  std::ifstream dictionaryDataSource;


  dictionaryDataSource.open("test.txt");

  if (!dictionaryDataSource.is_open())
  {
    std::cerr << "The input file was not opened.";
    return 1;
  }

  CommandExecutor().run(dictionaryDataSource);


  /*try
  {
    if (argc == ARGUMENT_COUNT_REQUIRED)
    {
      dictionaryDataSource.open(argv[1]);

      if (!dictionaryDataSource.is_open())
      {
        std::cerr << "The input file was not opened.";
        return 1;
      }

      CommandExecutor().run(dictionaryDataSource);
    }
    else
    {
      throw std::runtime_error("Invalid number of arguments.");
    }
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << std::endl;
    return 2;
  }*/
}
