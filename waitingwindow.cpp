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

void waitingWindow::setMax(int num)
{
  ui->progressBar->setMaximum(num);
}

void waitingWindow::setText(const QString text)
{
  ui->label->setText(text);
}

void waitingWindow::setCurr(int num)
{
  ui->progressBar->setValue(num);
}
