



#include <QApplication>
#include "qtreversimenudialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::reversi::QtReversiMenuDialog w;
  w.show();
  return a.exec();
}
