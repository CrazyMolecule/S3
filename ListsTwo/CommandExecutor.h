#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include <iostream>
#include <string>
#include <functional>
#include "Dictionary.h"
#include "Command.h"
#include "BidirectionalList.h"
#include "StringUtils.h"

namespace bavykin
{
  class CommandExecutor
  {
  public:
    CommandExecutor();

    void readFile(std::istream& input);
    void run(std::istream& input);

  private:
    dictionary< std::string, void (CommandExecutor::*)(list< std::string >) > m_RegisteredCommands;
    dictionary< std::string, list< int > > m_Lists;

    void checkIsThereListsNamesInMainDict(list< std::string > args);
    void print(list< std::string > args);
    void replace(list< std::string > args);
    void remove(list< std::string > args);
    void concat(list< std::string > args);
    void equal(list< std::string > args);
    void regCommand(std::string command, void (CommandExecutor::* function)(list< std::string >));
  };
}
#endif
