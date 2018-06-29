#include "reader.h"
#include "ui_reader.h"
#include<QIcon>
#include<QFont>
#include<QTableWidget>
#include<QPixmap>
#include<QLabel>
#include<QFrame>
#include<QDialog>
Reader::Reader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reader)
{
    ui->setupUi(this);
    handleEvents();

    this->setWindowTitle("图书管理");

    QIcon searchImage(":/image/search.png");
    ui->search->setIcon(searchImage);
    ui->search->setIconSize(QSize(85,46));
    ui->search->setFlat(true);
}

Reader::~Reader()
{
    delete ui;
}

void Reader::showReaderwin(QString& t)
{
    token = t;
    ui->tabWidget->removeTab(5);
    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);
    ui->tabWidget->removeTab(2);
    ui->deletebook_2->hide();
    this->show();
}
void Reader::showAdministratorwin(QString& t)
{
    token = t;
    ui->appoint->hide();
    ui->appointborrow->hide();
    ui->appointreturn->hide();
    this->show();
}
//切换界面，仅仅ui使用
void Reader::switchPage(int i)
{
    switch(i)
    {
    case GOOD_FIND:
        ui->searchStackedWidget->setCurrentIndex(1);
        break;
    case _FIND:
        ui->searchStackedWidget->setCurrentIndex(0);
        break;
    case ADD_BOOK:
        ui->OPERATEBOOK->setCurrentIndex(0);
        break;
    case DELETE_BOOK:
        ui->OPERATEBOOK->setCurrentIndex(1);
        break;
    case MODIFY_BOOK:
        ui->OPERATEBOOK->setCurrentIndex(2);
        break;
    case MODIFY_BOOK_GROUP:
        ui->OPERATEBOOK->setCurrentIndex(3);
        break;
    case ADD_READER:
        ui->readerStackedWidget->setCurrentIndex(0);
        break;
    case DELETE_READER:
        ui->readerStackedWidget->setCurrentIndex(1);
        break;
    case MODIFY_READER:
        ui->readerStackedWidget->setCurrentIndex(2);
        break;
    case MODIFY_READER_GROUP:
        ui->readerStackedWidget->setCurrentIndex(3);
        break;
    case ADD_GROUP:
        ui->groupStackedWidget->setCurrentIndex(0);
        break;
    case DELETE_GROUP:
        ui->groupStackedWidget->setCurrentIndex(1);
        break;
    case MODIFY_GROUP:
        ui->groupStackedWidget->setCurrentIndex(2);
        break;
    case BORROW_BOOK:
        ui->brbookStackedWidget->setCurrentIndex(0);
        break;
    case RETURN_BOOK:
        ui->brbookStackedWidget->setCurrentIndex(1);
        break;
    }
}
//生成表格
void Reader::Result(QTableWidget* tab)
{
    tab->setColumnCount(14);//设置列数
    tab->setRowCount(10);

    tab->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tab->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//表头颜色
    tab->horizontalHeader()->setFixedHeight(40);
    //tab->horizontalHeader()->setDefaultSectionSize(150);//宽度//应该可以不用设置
    //tab->horizontalHeader()->setEnabled(false);//不可点击

    QStringList header;
    header<<tr("选择图书")<<tr("封面")<<tr("ID")<<tr("书名")<<tr("groupID")
         <<tr("作者")<<tr("出版社")<<tr("tags")<<tr("IBSN")<<tr("价格")<<tr("页数")
        <<tr("书架号")<<tr("入馆时间")<<tr("Available");
    tab->setHorizontalHeaderLabels(header);  //标签

   //添加复选框
    for(int i=0;i<10;i++)
    {
        QTableWidgetItem *checkBox = new QTableWidgetItem();
        checkBox->setCheckState(Qt::Unchecked);
        checkBox->setText("勾选启用");
        tab->setItem(i, 0, checkBox);
    }

    tab->setItem(0,3,new QTableWidgetItem("《藏地密码》"));//添加内容

}

void Reader::handleEvents()
{
    //search切换
    connect(ui->GOODFIND,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(GOOD_FIND);
    });
    connect(ui->FIND,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(_FIND);
    });

    //book添加删除修改信息页面切换
    connect(ui->ADDBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_BOOK);
    });
    connect(ui->DELETEBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(DELETE_BOOK);
    });
    connect(ui->MODIFYBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_BOOK);
    });
    connect(ui->MODIFYBOOKGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_BOOK_GROUP);
    });

    //reader添加删除修改信息页面切换
    connect(ui->ADDREADER,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_READER);
    });
    connect(ui->DELETEREADER,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(DELETE_READER);
    });
    connect(ui->MODIFYREADER,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_READER);
    });
    connect(ui->MODIFYREADERGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_READER_GROUP);
    });

    //group添加删除修改信息页面切换
    connect(ui->ADDGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_GROUP);
    });
    connect(ui->DELETEGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(DELETE_GROUP);
    });
    connect(ui->MODIFYGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_GROUP);
    });

    //借还管理界面切换
    connect(ui->BORROWBOOK,&QPushButton::clicked,
    [=]()
    {
        Reader::switchPage(BORROW_BOOK);
        Result(ui->searchResult_3);
    });
    connect(ui->RETURNBOOK,&QPushButton::clicked,
    [=]()
    {
        Reader::switchPage(RETURN_BOOK);
        Result(ui->searchResult_4);
    });
    //查询按钮
    connect(ui->search,&QPushButton::clicked,
            [=]()
    {
        Result(ui->searchResult);
    });
    connect(ui->search_2,&QPushButton::clicked,
            [=]()
    {
        Result(ui->searchResult_5);
    });
    //tabwidget点击
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,this,&Reader::on_tabWidget_tabBarClicked);
    //表格点击
    connect(ui->searchResult,&QTableWidget::cellClicked,this,&Reader::on_searchResult_cellClicked);

    connect(ui->BACK,&QPushButton::clicked,
            [=]()
    {
        ui->BOOKVIEW->setCurrentIndex(0);
    });

}

void Reader::on_searchResult_cellClicked(int row, int column)
{
    ui->BOOKVIEW->setCurrentIndex(1);
}

void Reader::on_tabWidget_tabBarClicked(int index)
{
    if(index == 1)
    {
        Result(ui->searchResult_2);
    }
}
