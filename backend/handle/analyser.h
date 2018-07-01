#pragma once
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QVariant>
#include <QList>
#include <QMap>

class analyser
{
protected:
    QJsonObject& json;
public:
    QString detail;
    QString token;
    bool result;
    analyser(QJsonObject& _json);
};

class infoObject
{
    QMap<QString, QVariant> info;
public:
    infoObject(QJsonObject _json);
    QVariant take(const QString &key);
};

class infoanalyser: public analyser
{
    QVector<infoObject*> info;
public:
    infoanalyser(QJsonObject& _json);
};
