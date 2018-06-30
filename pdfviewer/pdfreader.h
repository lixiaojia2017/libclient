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

#ifndef PDFREADER_H
#define PDFREADER_H

#include <QMainWindow>
#include <QCloseEvent>
#include <set>

class QAction;
class QPdfWidget;
/**
 * @brief PDF viewer main window.
 */
class PDFReader : public QMainWindow
{
    Q_OBJECT
public:

    PDFReader(QWidget *pParent = nullptr, Qt::WindowFlags flags = 0);
    std::set<uint> getBookmark()const;
    void closeEvent(QCloseEvent *event)override;
public slots:

    void loadFile(const QString &path);
    void loadData(const QByteArray &data);

private slots:

    void onOpenFile();

private:
    //void createActions();
    //void createToolBar();

    //QAction *m_pOpenFileAction;
    QPdfWidget *m_pPdfWidget;
};

#endif // PDFREADER_H
