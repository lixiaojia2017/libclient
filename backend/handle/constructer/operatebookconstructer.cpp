#include "operatebookconstructer.h"

operatebookconstructer::operatebookconstructer(const QString& token): constructer(token)
{
    jsonReturn.insert("type", "OPERATEBOOK");
}

createbook::createbook(const QMap<QString, QVariant> _info, const QString& token)
    : operatebookconstructer(token)
{
    jsonReturn.insert("command", "createbook");
    QJsonArray info;
    for(auto iter = _info.begin(); iter != _info.end(); iter++)
    {
        QJsonObject infoa;
        infoa.insert("field", iter.key());
        if(iter.key() == "tags")
        {
            infoa.insert("data", QJsonArray::fromVariantList(iter.value().toList()));
        }
        else
        {
            infoa.insert("data", QJsonValue::fromVariant(iter.value()));
        }
        info.append(infoa);
    }
    jsonReturn.insert("info", info);
}

deletebook::deletebook(const QList<QVariant> &bookid, const QString &token)
    : operatebookconstructer(token)
{
    jsonReturn.insert("command", "deletebook");
    jsonReturn.insert("bookid", QJsonArray::fromVariantList(bookid));
}

changebook::changebook(int bookid, const QMap<QString, QVariant> _info, const QString &token)
    : operatebookconstructer(token)
{
    jsonReturn.insert("command", "changebook");
    jsonReturn.insert("bookid", bookid);
    QJsonArray info;
    for(auto iter = _info.begin(); iter != _info.end(); iter++)
    {
        QJsonObject infoa;
        infoa.insert("field", iter.key());
        if(iter.key() == "tags")
        {
            infoa.insert("data", QJsonArray::fromVariantList(iter.value().toList()));
        }
        else
        {
            infoa.insert("data", QJsonValue::fromVariant(iter.value()));
        }
        info.append(infoa);
    }
    jsonReturn.insert("info", info);
}

changegroup::changegroup(int groupid, const QList<QVariant> &bookid, const QString &token)
    : operatebookconstructer(token)
{
    jsonReturn.insert("command", "changegroup");
    jsonReturn.insert("groupid", groupid);
    jsonReturn.insert("bookid", QJsonArray::fromVariantList(bookid));
}
