#pragma GCC diagnostic push



#include <QApplication>
#include "qtreversimenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::reversi::QtReversiMenuDialog w;
  w.show();
  return a.exec();
}
