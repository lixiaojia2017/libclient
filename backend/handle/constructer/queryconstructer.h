#pragma once

#include <QVector>
#include "abstractconstructer.h"

class queryconstructer: public constructer
{
public:
    queryconstructer(const QString& token);
};

class querybook: public queryconstructer
{
public:
    querybook(const QString &rule, const QList<QVariant> &order, int records, int page, const QMap<QString, QVariant> _info, const QString &token);
    querybook(const QString &rule, const QList<QVariant> &order, int records, int page, const QString &_info, const QString &token);
};

class queryinfo: public queryconstructer
{
public:
    queryinfo(const QList<QVariant> &order, int records, int page, const QString &table, const QString &conditions, const QString &token);
};
