#pragma GCC diagnostic push


#include "reversimenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char * argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::reversi::MenuDialog().Execute(args);
}

