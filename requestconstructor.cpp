#include "requestconstructor.h"
RequestConstructor::RequestConstructor(QObject *root):root(root)
{
}

QJsonDocument* RequestConstructor::getResult(){
    construct(root);
    QJsonDocument* js=new QJsonDocument;
    *js=QJsonDocument::fromVariant(result);
    return js;
}
RequestConstructor::~RequestConstructor(){}
void RequestConstructor::construct(QObject *root){
        for(auto it=root->children().begin();it!=root->children().end();it++){
            QLineEdit* t;
            t=dynamic_cast<QLineEdit*>(*it);
            if(t!=nullptr){
                result[t->objectName()]=t->text();
            }
        }

}
