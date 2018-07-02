#include "operateuserconstructer.h"

operateuserconstructer::operateuserconstructer(const QString& token): constructer(token)
{
    jsonReturn.insert("type", "OPERATEUSER");
}

createuser::createuser(const QMap<QString, QVariant> &_info, const QString &token)
: operateuserconstructer(token)
{
    jsonReturn.insert("command", "createuser");
    QJsonArray info;
    for(auto iter = _info.begin(); iter != _info.end(); iter++)
    {
        QJsonObject infoa;
        infoa.insert("field", iter.key());
        infoa.insert("data", iter.value().toString());
        info.push_back(infoa);
    }
    jsonReturn.insert("info", info);
}

deleteuser::deleteuser(const QList<QVariant> &userid, const QString &token)
: operateuserconstructer(token)
{
    jsonReturn.insert("command", "deleteuser");
    jsonReturn.insert("userid", QJsonArray::fromVariantList(userid));
}

changeusergroup::changeusergroup(int groupid, const QList<QVariant> &userid, const QString &token)
: operateuserconstructer(token)
{
    jsonReturn.insert("command", "changegroup");
    jsonReturn.insert("grooupid", groupid);
    jsonReturn.insert("userid", QJsonArray::fromVariantList(userid));
}
