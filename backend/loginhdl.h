#ifndef LOGINHDL_H
#define LOGINHDL_H
#include "responsehdl.h"
class LoginHdl:public ResponseHdl
{
    Q_OBJECT
public:
    LoginHdl(QJsonObject* rsp);
    virtual void deal();
    virtual ~LoginHdl();
signals:
    void onSuccess(QString&);
    void onFailed(QString&);
};
#endif // LOGINHDL_H
