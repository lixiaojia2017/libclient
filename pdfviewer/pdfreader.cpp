/*
                          qpdf

    Copyright (C) 2015 Arthur Benilov,
    arthur.benilov@gmail.com
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.
*/

#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QMessageBox>
#include "QPdfWidget"
#include "pdfreader.h"

#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

PDFReader::PDFReader(QWidget *pParent, Qt::WindowFlags flags)
    : QMainWindow(pParent, flags)
{
    setWindowIcon(QIcon(":/icons/pdf.png"));

    m_pPdfWidget = new QPdfWidget();
    setCentralWidget(m_pPdfWidget);

    //createActions();
    //createToolBar();
}

void PDFReader::loadFile(const QString &path)
{
    if (m_pPdfWidget->loadFile(path)) {
        // Update window title with the file name
        QFileInfo fi(path);
        setWindowTitle(fi.fileName());
    }
}

void PDFReader::loadData(const QByteArray &data)
{
  m_pPdfWidget->loadData(data);
}

std::set<uint> PDFReader::getBookmark()const
{
    return m_pPdfWidget->bookmark;
}

//void PDFReader::createActions()
//{
    //m_pOpenFileAction = new QAction(QIcon(":/icons/folder.png"), tr("&Open..."), this);
    //connect(m_pOpenFileAction, &QAction::triggered, this, &MainWindow::onOpenFile);
//}

//void PDFReader::createToolBar()
//{
//    QToolBar *pToolBar = addToolBar(tr("File"));
//    pToolBar->setMovable(false);
    //pToolBar->addAction(m_pOpenFileAction);
//}

void PDFReader::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open PDF file"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    tr("PDF file (*.pdf)"));
    if (fileName.isEmpty()) {
        return;
    }

    loadFile(fileName);
}

void PDFReader::closeEvent(QCloseEvent *event)
{
  QMessageBox::StandardButton button;
  button = QMessageBox::question(this,tr("退出程序"),QString(tr("确认退出程序")),QMessageBox::Yes|QMessageBox::No);
  if(button==QMessageBox::No)
      {
          event->ignore();
      }
      else if(button==QMessageBox::Yes)
      {
          event->accept();
      }
}
