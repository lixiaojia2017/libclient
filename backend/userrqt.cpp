#include "userrqt.h"

UserRqt::UserRqt(QString token):AbstractRqt(token){
    rqt.insert("type","USER");
}
UserRqt::~UserRqt(){}
void UserRqt::construct(const QString &command, const QObject *root){
    QByteArray cpath = command.toLocal8Bit();
        char* cmd = cpath.data();
        rqt.insert("command",command);
        QMetaEnum me = QMetaEnum::fromType<UserRqt::CMD>();
        switch(me.keyToValue(cmd))
        {
        case updateinfo:
        {QJsonArray arr;
            for(auto it=root->children().begin();it!=root->children().end();it++){
                QLineEdit* t;
                t=dynamic_cast<QLineEdit*>(*it);
                if(t!=nullptr){
                    QJsonObject obj{
                        {"field", t->objectName()},
                        {"data", t->text()}
                                              };
                    arr.append(obj);
                }
            }
            rqt.insert("info",arr);}
            break;
        default:
            AbstractRqt::construct(command,root);
            for(auto it=root->children().begin();it!=root->children().end();it++){
                    QComboBox* c;
                    c=dynamic_cast<QComboBox*>(*it);
                    if(c!=nullptr){
                        rqt.insert(c->objectName(),c->currentText());
                }
            }
            break;
        }
        switch(me.keyToValue(cmd))
        {
        case login:
        {
            QString tmp=rqt.take("password").toString();
            // here we don't automatically use MD5 since password should be encrypted outside
            rqt.insert("password",tmp);
            break;}
        case changepwd:
        {
            QString tmp=rqt.take("oldpwd").toString();
            rqt.insert("oldpwd",token::getMD5(tmp));
            tmp=rqt.take("newpwd").toString();
            rqt.insert("newpwd",token::getMD5(tmp));
            break;}
        default:
            break;
        }
}
