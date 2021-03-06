



#include "qtreversimenudialog.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "reversimenudialog.h"
#include "qtaboutdialog.h"

#include "qtreversimaindialog.h"
#include "reversimenudialog.h"
#include "ui_qtreversimenudialog.h"



ribi::reversi::QtReversiMenuDialog::QtReversiMenuDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtReversiMenuDialog)
{
  ui->setupUi(this);
}

ribi::reversi::QtReversiMenuDialog::~QtReversiMenuDialog() noexcept
{
  delete ui;
}

void ribi::reversi::QtReversiMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape) { close(); }
}

void ribi::reversi::QtReversiMenuDialog::on_button_start_clicked() noexcept
{
  QtReversiMainDialog d;
  this->ShowChild(&d);
}

void ribi::reversi::QtReversiMenuDialog::on_button_about_clicked() noexcept
{
  QtAboutDialog d(MenuDialog().GetAbout());
  d.setWindowIcon(windowIcon());
  d.setStyleSheet(styleSheet());
  ShowChild(&d);
}

void ribi::reversi::QtReversiMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}
