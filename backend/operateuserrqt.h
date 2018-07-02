#ifndef OPERATEUSERRQT_H
#define OPERATEUSERRQT_H
#include "abstractrqt.h"
#include "token.h"
class OperateUserRqt:public AbstractRqt
{
    Q_OBJECT
public:
    enum CMD
        {
            createuser,
            deleteuser,
            changegroup
        };
        Q_ENUM(CMD)
    OperateUserRqt(QString token);
    void construct(const QString& cmd,const QObject* root);
}
#endif // OPERATEUSERRQT_H
