#ifndef READER_H
#define READER_H

#include <QMainWindow>

namespace Ui {
class Reader;
}

class Reader : public QMainWindow
{
    Q_OBJECT

public:
    explicit Reader(QWidget *parent = 0);
    ~Reader();

private slots:
    void showwin();

protected:
    void switchPage();

private:
    Ui::Reader *ui;
};

#endif // READER_H
