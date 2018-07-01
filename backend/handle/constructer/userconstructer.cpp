#include "userconstructer.h"


userconstructer::userconstructer(const QString& token): constructer(token)
{
    jsonReturn.insert("type", "USER");
}

userlogin::userlogin(const QString &username, const QString &password, const QString &group)
    : userconstructer("unknown")
{
    jsonReturn.insert("command", "login");
    jsonReturn.insert("username", username);
    jsonReturn.insert("password", password);
    jsonReturn.insert("group", group);
}

userforget::userforget(const QString &username, const QString &group, const QString &auth)
    : userconstructer("unknown")
{
    jsonReturn.insert("command", "forget");
    jsonReturn.insert("username", username);
    jsonReturn.insert("auth", auth);
    jsonReturn.insert("group", group);
}

userlogout::userlogout(const QString &token)
    : userconstructer(token)
{
    jsonReturn.insert("command", "logout");
}

userchangepwd::userchangepwd(const QString &oldpwd, const QString &newpwd, const QString &token)
    : userconstructer(token)
{
    jsonReturn.insert("command", "changepwd");
    jsonReturn.insert("oldpwd", oldpwd);
    jsonReturn.insert("newpwd", newpwd);
}

userupdateinfo::userupdateinfo(const QMap<QString, QVariant> &_info, const QString &token)
    : userconstructer(token)
{
    jsonReturn.insert("command", "updateinfo");
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
