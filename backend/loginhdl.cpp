#include "loginhdl.h"
LoginHdl::LoginHdl(QJsonObject* rsp):ResponseHdl(rsp){}

void LoginHdl::deal(){
    if(rsp->take("result").toBool()){
        QString token=rsp->take("token").toString();
        emit(onSuccess(token));
    }
    else{
        QString err=rsp->take("detail").toString();
        emit(onFailed(err));
    }
}

LoginHdl::~LoginHdl(){
}
