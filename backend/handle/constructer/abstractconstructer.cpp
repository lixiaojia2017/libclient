#include "abstractconstructer.h"

constructer::constructer(const QString& token)
{
    jsonReturn.insert("token", token);
}

QJsonObject constructer::GetReturn()
{
    return jsonReturn;
}

constructer::~constructer(){}
