#ifndef READER_H
#define READER_H

#include <QMainWindow>
#include <QString>
#include<QTableWidget>
namespace Ui {
class Reader;
}


#define GOOD_FIND 0
#define _FIND 1

#define ADD_BOOK 2
#define DELETE_BOOK 3
#define MODIFY_BOOK 4
#define MODIFY_BOOK_GROUP 5

#define ADD_READER 6
#define DELETE_READER 7
#define MODIFY_READER 8
#define MODIFY_READER_GROUP 9

#define ADD_GROUP 10
#define DELETE_GROUP 11
#define MODIFY_GROUP 12
#define BORROW_BOOK 13
#define RETURN_BOOK 14



class Reader : public QMainWindow
{
    Q_OBJECT

public:
    explicit Reader(QWidget *parent = 0);
    ~Reader();
public slots:
    void showReaderwin(QString&);
    void showAdministratorwin(QString&);
private slots:
    void on_searchResult_cellClicked(int row, int column);

    void on_tabWidget_tabBarClicked(int index);

protected:
    void switchPage(int);
    void Result(QTableWidget* tab);

private:
    Ui::Reader *ui;
    QString token;
    void handleEvents();
};

#endif // READER_H
