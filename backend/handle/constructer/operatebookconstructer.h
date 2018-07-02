<<<<<<< HEAD
#pragma once

#include "abstractconstructer.h"

class operatebookconstructer: public constructer
{
public:
    operatebookconstructer(const QString& token);
};

class createbook: public operatebookconstructer
{
public:
    createbook(const QMap<QString, QVariant> _info, const QString& token);
};

class deletebook: public operatebookconstructer
{
public:
    deletebook(const QList<QVariant> &bookid, const QString &token);
};

class changebook: public operatebookconstructer
{
public:
    changebook(int bookid, const QMap<QString, QVariant> _info, const QString &token);
};

class changebookgroup: public operatebookconstructer
{
public:
    changebookgroup(int groupid, const QList<QVariant> &bookid, const QString &token);
};
=======
#pragma once

#include "abstractconstructer.h"

class operatebookconstructer: public constructer
{
public:
    operatebookconstructer(const QString& token);
};

class createbook: public operatebookconstructer
{
public:
    createbook(const QMap<QString, QVariant> _info, const QString& token);
};

class deletebook: public operatebookconstructer
{
public:
    deletebook(const QList<QVariant> &bookid, const QString &token);
};

class changebook: public operatebookconstructer
{
public:
    changebook(int bookid, const QMap<QString, QVariant> _info, const QString &token);
};

class changegroup: public operatebookconstructer
{
public:
    changegroup(int groupid, const QList<QVariant> &bookid, const QString &token);
};
>>>>>>> a37eb6a22424f0d495aa07d1705b0a268e6e8277
