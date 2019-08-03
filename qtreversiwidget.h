#ifndef QTREVERSIWIDGET_H
#define QTREVERSIWIDGET_H





#include <boost/shared_ptr.hpp>

#include <QWidget>
#include "reversifwd.h"


namespace ribi {
namespace reversi {

class QtWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

signals:

private:
  boost::shared_ptr<Widget> m_reversi;
  QColor m_color_player1;
  QColor m_color_player2;
  QColor m_color_square_even;
  QColor m_color_square_odd;
  void mousePressEvent(QMouseEvent * e);
  void paintEvent(QPaintEvent *);
};

} //~namespace reversi
} //~namespace ribi

#endif // QTREVERSIWIDGET_H
