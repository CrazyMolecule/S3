#include "CommandExecutor.h"

namespace bavykin
{
  CommandExecutor::CommandExecutor()
  {
    regCommand("print", &CommandExecutor::print);
    regCommand("replace", &CommandExecutor::replace);
    regCommand("remove", &CommandExecutor::remove);
    regCommand("concat", &CommandExecutor::concat);
    regCommand("equal", &CommandExecutor::equal);
  }

  void CommandExecutor::readFile(std::istream& input)
  {
    std::string line = "";
    while (getline(input, line))
    {
      if (!line.empty())
      {
        list< std::string > splittedCommandLine = splitString(line, " ");
        const std::string listName = splittedCommandLine[0];
        list< int > fillingList(listName);
        splittedCommandLine.popFront();
        while (splittedCommandLine.size() > 0)
        {
          fillingList.pushBack(std::stoi(splittedCommandLine[0]));
          splittedCommandLine.popFront();
        }
        m_Lists.insert(listName, fillingList);
      }
    }
  }

  void CommandExecutor::run(std::istream& input)
  {
    readFile(input);

    std::string line = "";
    while (getline(std::cin, line))
    {
      if (!line.empty())
      {
        try
        {
          Command currentCommand(line);
          if (m_RegisteredCommands.contains(currentCommand.getOperation()))
          {
            void (CommandExecutor:: * operation)(list< std::string >);
            operation = m_RegisteredCommands[currentCommand.getOperation()];
            list< std::string > args = currentCommand.getArgs();
            (this->*operation)(args);
          }
          else
          {
            throw std::invalid_argument("The command is not registered.");
          }
        }
        catch (const std::invalid_argument&)
        {
          std::cout << "<INVALID COMMAND>" << std::endl;
        }
      }
    }
  }

  void CommandExecutor::checkIsThereListsNamesInMainDict(list< std::string > args)
  {
    for (size_t i = 1; i < args.size(); i++)
    {
      if (!m_Lists.contains(args[i]))
      {
        throw std::invalid_argument("Invalid argument.");
      }
    }
  }

  void CommandExecutor::print(list< std::string > args)
  {
    if (args.size() != 1)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    if (!m_Lists.contains(args[0]))
    {
      throw std::invalid_argument("Invalid argument.");
    }

    list< int > toPrint = m_Lists[args[0]];
    std::cout << toPrint << std::endl;
  }

  void CommandExecutor::replace(list< std::string > args)
  {
    if (args.size() != 3)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    if (!m_Lists.contains(args[0]))
    {
      throw std::invalid_argument("Invalid argument.");
    }

    bool convertToInt = false;
    if (!m_Lists.contains(args[2]))
    {
      convertToInt = true;
    }

    std::string dataSet = args[0];
    int toReplace = std::stoi(args[1]);
    std::string replaceWith = args[2];

    if (convertToInt)
    {
      m_Lists.insert(dataSet, m_Lists[dataSet].replace(toReplace, std::stoi(replaceWith)));
    }
    else
    {
      m_Lists.insert(dataSet, m_Lists[dataSet].replace(toReplace, m_Lists[replaceWith]));
    }
  }

  void CommandExecutor::remove(list< std::string > args)
  {
    if (args.size() != 2)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    if (!m_Lists.contains(args[0]))
    {
      throw std::invalid_argument("Invalid argument.");
    }

    bool convertToInt = false;
    if (!m_Lists.contains(args[1]))
    {
      convertToInt = true;
    }

    std::string dataSet = args[0];
    std::string removable = args[1];

    if (convertToInt)
    {
      m_Lists.insert(dataSet, m_Lists[dataSet].remove(std::stoi(removable)));
    }
    else
    {
      m_Lists.insert(dataSet, m_Lists[dataSet].remove(m_Lists[removable]));
    }
  }

  void CommandExecutor::concat(list< std::string > args)
  {
    if (args.size() < 3)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    std::string newDataSet = args[0];

    args.popFront();

    checkIsThereListsNamesInMainDict(args);

    list< list< int > > newListWithLists;

    for (size_t i = 0; i < args.size(); i++)
    {
      newListWithLists.pushBack(m_Lists[args[i]]);
    }

    list< int > concatedList(newDataSet);

    m_Lists.insert(newDataSet, concatedList.concat(newListWithLists));
  }

  void CommandExecutor::equal(list< std::string > args)
  {
    if (args.size() < 2)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    checkIsThereListsNamesInMainDict(args);

    list< list< int > > newListWithLists;

    for (size_t i = 0; i < args.size(); i++)
    {
      newListWithLists.pushBack(m_Lists[args[i]]);
    }

    list< int > comparator;
    std::cout << ((comparator.equal(newListWithLists)) ? "<TRUE>" : "<FALSE>") << std::endl;
  }

  void CommandExecutor::regCommand(std::string command, void (CommandExecutor::* function)(list< std::string >))
  {
    m_RegisteredCommands.insert(command, function);
  }
}
