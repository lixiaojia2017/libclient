#include "loadconstructer.h"

loadconstructer::loadconstructer(const QString& token): constructer(token)
{

}

uploadconstructer::uploadconstructer(const QString &file, int ID, const QString token)
: loadconstructer(token)
{

}

downloadconstructer::downloadconstructer(const QString &file, int ID, const QString token)
: loadconstructer(token)
{

}


