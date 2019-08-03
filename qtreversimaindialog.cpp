



#include "qtreversimaindialog.h"

#include "qtreversiwidget.h"
#include "ui_qtreversimaindialog.h"


ribi::reversi::QtReversiMainDialog::QtReversiMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtReversiMainDialog),
  m_reversi(new QtWidget)
{
  ui->setupUi(this);
  ui->layout->addWidget(m_reversi.get());
}

ribi::reversi::QtReversiMainDialog::~QtReversiMainDialog() noexcept
{
  delete ui;
}


