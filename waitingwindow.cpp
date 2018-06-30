#include "waitingwindow.h"
#include "ui_waitingwindow.h"

waitingWindow::waitingWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::waitingWindow)
{
  ui->setupUi(this);
  this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
}

waitingWindow::~waitingWindow()
{
  delete ui;
}
