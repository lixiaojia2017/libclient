#pragma once

#include "abstractconstructer.h"

class checkconstructer: public constructer
{
public:
    checkconstructer(const QString& token);
};

class checkborrow: public checkconstructer
{
public:
    checkborrow(int appointid, const QString& token);
};

class checkreturn: public checkconstructer
{
public:
    checkreturn(int appointid, const QString& token);
};
