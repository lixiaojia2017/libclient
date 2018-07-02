#include "appointconstructer.h"

appointconstructer::appointconstructer(const QString &token): constructer(token)
{
    jsonReturn.insert("type", "APPOINT");
}

appointborrow::appointborrow(const QString &appointtime, int id, const QString &token)
    : appointconstructer(token)
{
    jsonReturn.insert("command", "appointborrow");
    jsonReturn.insert("appointtime", appointtime);
    jsonReturn.insert("id", id);
}

appointreturn::appointreturn(int id, const QString &token)
    : appointconstructer(token)
{
    jsonReturn.insert("command", "appointreturn");
    jsonReturn.insert("id", id);
}
