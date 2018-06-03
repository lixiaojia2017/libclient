#ifndef APPOINTMENTRQT_H
#define APPOINTMENTRQT_H
#include "abstractrqt.h"
#include "token.h"
class AppointmentRqt:public AbstractRqt
{
    Q_OBJECT
public:
    enum CMD
        {
            appointborrow,
            appointreturn
        };
        Q_ENUM(CMD)
    AppointmentRqt(QString token);
    void construct(const QString& cmd,const QObject* root);
}

#endif // APPOINTMENTRQT_H
