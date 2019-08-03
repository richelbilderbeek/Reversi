#include "reversimenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>




#include <boost/lexical_cast.hpp>



#include "reversiboard.h"
#include "reversiwidget.h"

#include "reversimaindialog.h"

int ribi::reversi::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc > 3)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  int size = 4;
  if (argc == 3)
  {
    if (
         argv[1] != "-s" && argv[1] != "--size" && argv[1] != "-sz"
      && argv[1] !=  "s" && argv[1] !=  "size" && argv[1] !=  "sz"
    )
    {
      std::cout << "Warning: the correct argument flag should be '-s' or '--size'" << '\n';
      //Parse next value anyway
    }
  }
  if (argc > 1)
  {
    try
    {
      size = boost::lexical_cast<int>(argv[ argc - 1]);
    }
    catch (boost::bad_lexical_cast&)
    {
      std::cout << "Error: size must be an integer" << '\n';
      return 1;
    }
  }
  if (size < 4)
  {
    std::cout << "Error: the minimum board size is 4x4. Please supply a supported size" << '\n';
    return 1;
  }

  MainDialog d;
  d.Execute(size);
  return 0;
}

ribi::About ribi::reversi::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Reversi",
    "Reversi clone",
    "today",
    "200x-2015",
    "http://www.richelbilderbeek.nl/GameReversi.htm",
    GetVersion(),
    GetVersionHistory()
  );
  return a;
}

ribi::Help ribi::reversi::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('s',"size","set the size of the board (flag can also be omitted, default is 4)")
    },
    {
      "reversi -s 10",
      "reversi 10",
      "reversi"
    }
  );
}

std::string ribi::reversi::MenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::reversi::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: conformized to ProjectRichelBilderbeekConsole",
    "2015-12-17: version 2.0: moved to own GitHub",
  };
}
