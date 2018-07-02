#pragma once

#include "abstractconstructer.h"

class appointconstructer: public constructer
{
public:
    appointconstructer(const QString& token);
};

class appointborrow: public appointconstructer
{
public:
    appointborrow(const QString &appointtime, int id, const QString &token);
};

class appointreturn: public appointconstructer
{
public:
    appointreturn(int id, const QString &token);
};
