#ifndef REVERSIMAINDIALOG_H
#define REVERSIMAINDIALOG_H

#include <string>
#include <vector>



#include <boost/scoped_ptr.hpp>
#include "about.h"


namespace ribi {
namespace reversi {

struct MainDialog
{
  MainDialog();

  ///Start a Reversi game
  void Execute(const int size);
};

} //~namespace reversi
} //~namespace ribi

#endif // REVERSIMAINDIALOG_H
