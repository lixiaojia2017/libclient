#ifndef USERRQT_H
#define USERRQT_H
#include "abstractrqt.h"
#include "token.h"
class UserRqt:public AbstractRqt
{
    Q_OBJECT
public:
    ~UserRqt();
    enum CMD
        {
            login,
            forget,
            logout,
            changepwd,
            updateinfo
        };
        Q_ENUM(CMD)
    UserRqt(QString token);
    void construct(const QString& cmd,const QObject* root);
};
#endif // USERRQT_H
