#pragma once

#include "abstractconstructer.h"
#include "backend/token.h"

class loadconstructer: public constructer
{
public:
    loadconstructer(const QString& token);
};

class uploadconstructer: public loadconstructer
{
public:
    uploadconstructer(const QString &file, int ID, const QString token);
};

class downloadconstructer: public loadconstructer
{
public:
    downloadconstructer(const QString &file, int ID, const QString token);
};
