#ifndef READER_H
#define READER_H

#include"pdfviewer/pdfreader.h"
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
#define MODIFY_READER_GROUP 9

#define ADD_GROUP 10
#define DELETE_GROUP 11
#define MODIFY_GROUP 12
#define BORROW_BOOK 13
#define RETURN_BOOK 14

#define Initialization 101
#define Non_initialization 102

#define BOOK_GROUP_SEARCH 201
#define READER_GROUP_SEARCH 202

#define READER_IDENTITY 301
#define STAFFS_IDENTITY 302

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

    void on_tabWidget_tabBarClicked(int index);


    void on_logout_clicked();

    void on_searchResult_cellDoubleClicked(int row, int column);


protected:
    void switchPage(int);
    void Result(QTableWidget* tab);
    void ADDITEM(QTableWidget* tab,int);

private:
    Ui::Reader *ui;
    QString token;
    void handleEvents();

    PDFReader* pdfreader=nullptr;
};

#endif // READER_H
