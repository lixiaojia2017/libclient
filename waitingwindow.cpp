#include "waitingwindow.h"
#include "ui_waitingwindow.h"

waitingWindow::waitingWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::waitingWindow)
{
  ui->setupUi(this);
}

waitingWindow::~waitingWindow()
{
  delete ui;
}
