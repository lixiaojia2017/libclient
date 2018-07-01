#pragma once

#include "abstractconstructer.h"

class userconstructer: public constructer
{
public:
    userconstructer(const QString& token);
};

class userlogin: public userconstructer
{
public:
    userlogin(const QString &username, const QString &password, const QString &group);
};

class userforget: public userconstructer
{
public:
    userforget(const QString &username, const QString &group, const QString &auth);
};

class userlogout: public userconstructer
{
public:
    userlogout(const QString &token);
};

class userchangepwd: public userconstructer
{
public:
    userchangepwd(const QString &oldpwd, const QString &newpwd, const QString &token);
};

class userupdateinfo: public userconstructer
{
public:
    userupdateinfo(const QMap<QString, QVariant> &info,const QString &token);
};



