#include "analyser.h"

analyser::analyser(QJsonObject& _json): json(_json)
{
    token = json.value("token").toBool();
    result = json.value("result").toBool();
    if(!result)
    {
        detail = json.value("detail").toString();
    }
}

infoObject::infoObject(QJsonObject _json)
{
    for(auto iter = _json.begin(); iter != _json.end(); iter++)
    {
        if(iter.value().isArray())
        {
            QList<QVariant> infoArray;
            for(auto iter1 : iter.value().toArray())
            {
                infoArray.append(iter1.toVariant());
            }
            info.insert(iter.key(), infoArray);
        }
        else
        {
            info.insert(iter.key(), iter.value().toVariant());
        }
    }
}

QVariant infoObject::take(const QString &key)
{
    return info[key];
}

infoanalyser::infoanalyser(QJsonObject& _json): analyser(_json)
{
    QJsonArray infoArray = json.value("info").toArray();
    for(auto iter : infoArray)
    {
        info.push_back(new infoObject(iter.toObject()));
    }
}
