#ifndef WAITINGWINDOW_H
#define WAITINGWINDOW_H

#include <QWidget>

namespace Ui {
  class waitingWindow;
}

class waitingWindow : public QWidget
{
  Q_OBJECT

public:
  explicit waitingWindow(QWidget *parent = 0);
  ~waitingWindow();

private:
  Ui::waitingWindow *ui;
};

#endif // WAITINGWINDOW_H
