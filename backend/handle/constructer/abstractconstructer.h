#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QVector>
#include <QVariant>
#include "backend/token.h"

class constructer:public QObject
{
public:
    constructer(const QString& token);
    virtual ~constructer() = 0;
    QJsonObject GetReturn();

protected:
    QJsonObject jsonReturn;
};
