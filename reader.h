﻿#ifndef READER_H
#define READER_H

#include"pdfviewer/pdfreader.h"
#include <QMainWindow>
#include <QString>
#include<QTableWidget>
#include "backend/handle/constructer/userconstructer.h"
#include "backend/handle/constructer/queryconstructer.h"
#include "backend/socketthread.h"
#include "waitingwindow.h"
#include "backend/handle/analyser.h"
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
    void setServer(QString addr, int p);
    void setUsername(const QString username);
public slots:
    void showReaderwin(QString&,QString&,int,int);
    void showAdministratorwin(QString&,QString&,int,int);
private slots:
    void on_tabWidget_tabBarClicked(int index);
    void on_logout_clicked();
    void on_searchResult_cellDoubleClicked(int row, int column);
    void on_search_clicked();
    void on_last_clicked();
    void on_next_clicked();
    void on_pushButton_13_clicked();
    void reset_page();
    void on_ngetnewr_clicked();
    void on_changepwd_clicked();
    void on_pushButton_5_clicked();
    void on_appointborrowpushbutton_clicked();
    void on_appointreturnpushbutton_clicked();
    void on_pushButton_clicked();

    void on_createbook_clicked();
    void on_changebook_clicked();
    void on_pushButton_6_clicked();

    void on_deletebook_2_clicked();


    void on_search_3_clicked();

    void on_searchBookgroup_clicked();

    void on_searchReadergroup_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();


    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_20_clicked();

    void on_deletereader_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_9_clicked();

    void on_BORROWBOOK_clicked();

    void on_RETURNBOOK_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

protected:
    void switchPage(int);
    void Result(QTableWidget* tab);
    void ADDITEM(QTableWidget* tab,infoanalyser& hdl);

private:
    waitingWindow wait;
    Ui::Reader *ui;
    QString token;
    QString serverAddr;
    int serverport;
    void handleEvents();
    QString username="NULL";
    int userID;
    PDFReader* pdfreader=nullptr;
    bool requested = false;
};

#endif // READER_H
