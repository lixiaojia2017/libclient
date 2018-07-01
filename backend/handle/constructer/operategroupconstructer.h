#pragma once

#include "abstractconstructer.h"

class operategroupconstructer: public constructer
{
public:
    operategroupconstructer(const QString& token);
};

class creategroup: public operategroupconstructer
{
public:
    // command 为 user,book,staff
    creategroup(const QString &command, const QMap<QString, QVariant> &_info, const QString &token);
};

class deletegroup: public operategroupconstructer
{
public:
    // command 为 user,book,staff
    deletegroup(const QString &command, int groupid, const QString &token);
};

class changegroup: public operategroupconstructer
{
public:
    // command 为 user,book,staff
    changegroup(const QString &command, int groupid, const QMap<QString, QVariant> &_info, const QString &token);
};
