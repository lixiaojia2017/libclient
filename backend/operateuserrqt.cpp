#include "operateuserrqt.h".h"

OperateUserRqt::OperateUserRqt(QString token):AbstractRqt(token){
    rqt.insert("type","OPERATEUSER");
}

void OperateUserRqt::construct(const QString &command, const QObject *root){
    QByteArray cpath = command.toLocal8Bit();
        char* cmd = cpath.data();
        rqt.insert("command",command);
        QMetaEnum me = QMetaEnum::fromType<OperateUserRqt::CMD>();
        switch(me.keyToValue(cmd))
        {
        case createuser:
            QJsonArray arr;
            for(auto it=root->children().begin();it!=root->children().end();it++){
                QLineEdit* t;
                t=dynamic_cast<QLineEdit*>(*it);
                if(t!=nullptr){
                    QJsonObject obj{
                        {"field", t->objectName()},
                        {"data", t->text()}
                                              };
                    if(t->objectName()=="password"){
                        obj.insert("data",token::getMD5(t->text()));
                    }
                    arr.append(obj);
                }
            }
            rqt.insert("info",arr);
            break;
        default:
            AbstractRqt::construct(command,root);
            break;
        }
}
