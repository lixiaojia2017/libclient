#pragma once

#include "abstractconstructer.h"

class operateuserconstructer: public constructer
{
public:
    operateuserconstructer(const QString& token);
};

class createuser : public operateuserconstructer
{
public:
    createuser(const QMap<QString, QVariant> &_info, const QString &token);
};

class deleteuser : public operateuserconstructer
{
public:
    deleteuser(const QList<QVariant> &userid, const QString &token);
};

class changeusergroup : public operateuserconstructer
{
public:
    changeusergroup(int groupid, const QList<QVariant> &userid, const QString &token);
};
