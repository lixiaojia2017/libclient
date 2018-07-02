#include "operategroupconstructer.h"

operategroupconstructer::operategroupconstructer(const QString& token): constructer(token)
{
    jsonReturn.insert("type", "OPERATEGROUP");
}

creategroup::creategroup(const QString &command, const QMap<QString, QVariant> &_info, const QString &token)
: operategroupconstructer(token)
{
    jsonReturn.insert("command", "create" + command);
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

deletegroup::deletegroup(const QString &command, int groupid, const QString &token)
: operategroupconstructer(token)
{
    jsonReturn.insert("command", "delete" + command);
    jsonReturn.insert("groupid", groupid);
}

changegroup::changegroup(const QString &command, int groupid, const QMap<QString, QVariant> &_info, const QString &token)
: operategroupconstructer(token)
{
    jsonReturn.insert("command", "change" + command);
    jsonReturn.insert("groupid", groupid);
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


