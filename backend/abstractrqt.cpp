#include "abstractrqt.h"
AbstractRqt::AbstractRqt(QString token){
    rqt.insert("token",token);
}
AbstractRqt::~AbstractRqt(){}
QJsonDocument* AbstractRqt::getRequest(){
    return new QJsonDocument(rqt);
}
void AbstractRqt::construct(const QString &cmd, const QObject *root){
    for(auto it=root->children().begin();it!=root->children().end();it++){
        QLineEdit* t;
        t=dynamic_cast<QLineEdit*>(*it);
        if(t!=nullptr){
            rqt.insert(t->objectName(),t->text());
        }
    }
}
