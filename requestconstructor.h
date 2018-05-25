#ifndef REQUESTCONSTRUCTOR_H
#define REQUESTCONSTRUCTOR_H
#include <QDataStream>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLineEdit>
class RequestConstructor
{
public:
    RequestConstructor(QObject *root);
    virtual ~RequestConstructor();
    QJsonDocument* getResult();
    virtual void construct(QObject *root);
private:
    QObject *root;
    QVariantMap result;
};
#endif // REQUESTCONSTRUCTOR_H
