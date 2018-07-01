#include "checkconstructer.h"

checkconstructer::checkconstructer(const QString& token): constructer(token)
{
    jsonReturn.insert("type", "CHECK");
}

checkborrow::checkborrow(int appointid, const QString& token): checkconstructer(token)
{
    jsonReturn.insert("command", "checkborrow");
    jsonReturn.insert("appointid", appointid);
}

checkreturn::checkreturn(int appointid, const QString& token): checkconstructer(token)
{
    jsonReturn.insert("command", "checkreturn");
    jsonReturn.insert("appointid", appointid);
}
