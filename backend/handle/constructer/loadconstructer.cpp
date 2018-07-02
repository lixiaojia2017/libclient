#include "loadconstructer.h"

loadconstructer::loadconstructer(const QString& token): constructer(token)
{
    jsonReturn.insert("type", "LOAD");
}

uploadconstructer::uploadconstructer(const QString &file, int ID, const QString token)
: loadconstructer(token)
{
    jsonReturn.insert("command", "up");
    jsonReturn.insert("id", ID);
    jsonReturn.insert("file", file);
}

downloadconstructer::downloadconstructer(const QString &file, int ID, const QString token)
: loadconstructer(token)
{
    jsonReturn.insert("command", "down");
    jsonReturn.insert("id", ID);
    jsonReturn.insert("file", file);
}


