#ifndef RESPONSEHDL_H
#define RESPONSEHDL_H
#include <QString>
#include <QObject>
#include <QJsonObject>
class ResponseHdl:public QObject
{
    Q_OBJECT
protected:
    QJsonObject* rsp;
public:
    ResponseHdl(QJsonObject* rsp);
    virtual void deal();
    virtual ~ResponseHdl();
signals:
    void onSuccess();
    void onFailed(QString&);
};
#endif // RESPONSEHDL_H
