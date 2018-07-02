#include "queryconstructer.h"

queryconstructer::queryconstructer(const QString& token): constructer(token)
{
    jsonReturn.insert("type", "QUERY");
}

// completesearch / fuzzysearch
// _info是一个QMap，其中的tags和bookcase的value为QList<QVariant>，price为QMap<QString, double>

querybook::querybook(const QString &rule, const QList<QVariant> &order, int records, int page, const QMap<QString, QVariant> _info, const QString &token)
    : queryconstructer(token)
{
    jsonReturn.insert("command", "book");
    jsonReturn.insert("rule", rule);
    jsonReturn.insert("order", QJsonValue::fromVariant(order));
    jsonReturn.insert("records", records);
    jsonReturn.insert("page", page);
    QJsonArray info;
    for(auto iter = _info.begin(); iter != _info.end(); iter++)
    {
        QJsonObject infoa;
        infoa.insert("field", iter.key());
        if(iter.key() == "tags" || iter.key() == "bookcase")
        {
            infoa.insert("data", QJsonArray::fromVariantList(iter.value().toList()));
        }
        else if(iter.key() == "price")
        {
            QJsonObject value;
            value.insert("inf", iter.value().toMap()["inf"].toDouble());
            value.insert("sup", iter.value().toMap()["sup"].toDouble());
            infoa.insert("data", value);
        }
        else
        {
            infoa.insert("data", QJsonValue::fromVariant(iter.value()));
        }
        info.append(infoa);
    }
    jsonReturn.insert("info", info);
}


// intelligentsearch

querybook::querybook(const QString &rule, const QList<QVariant> &order, int records, int page, const QString &_info, const QString &token)
    : queryconstructer(token)
{
    jsonReturn.insert("command", "book");
    jsonReturn.insert("rule", rule);
    jsonReturn.insert("order", QJsonValue::fromVariant(order));
    jsonReturn.insert("records", records);
    jsonReturn.insert("page", page);
    jsonReturn.insert("info", _info);
}

queryinfo::queryinfo(const QList<QVariant> &order, int records, int page, const QString &table, const QString &conditions, const QString &token)
    : queryconstructer(token)
{
    jsonReturn.insert("command", "info");
    jsonReturn.insert("order", QJsonValue::fromVariant(order));
    jsonReturn.insert("records", records);
    jsonReturn.insert("table", table);
    jsonReturn.insert("page", page);
    jsonReturn.insert("conditions", conditions);
}
