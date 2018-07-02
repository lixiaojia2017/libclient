#ifndef ABSTRACTRQT_H
#define ABSTRACTRQT_H

#include <QDataStream>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMetaEnum>
#include <QLineEdit>
#include <QComboBox>
class AbstractRqt:public QObject
{
    Q_OBJECT
public:
    AbstractRqt(QString token);
    virtual ~AbstractRqt();
    virtual void construct(const QString& cmd,const QObject* root);
    QJsonDocument* getRequest();
protected:
    QJsonObject rqt;
};
#endif // ABSTRACTRQT_H
