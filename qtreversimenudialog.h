#ifndef QTREVERSIMENUDIALOG_H
#define QTREVERSIMENUDIALOG_H





#include "qthideandshowdialog.h"


namespace Ui {
class QtReversiMenuDialog;
}

namespace ribi {
namespace reversi {

class QtReversiMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT
    
public:
  explicit QtReversiMenuDialog(QWidget *parent = 0) noexcept;
  QtReversiMenuDialog(const QtReversiMenuDialog&) = delete;
  QtReversiMenuDialog& operator=(const QtReversiMenuDialog&) = delete;
  ~QtReversiMenuDialog() noexcept;
    
private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtReversiMenuDialog *ui;

};

} //~namespace reversi
} //~namespace ribi

#endif // QTREVERSIMENUDIALOG_H
