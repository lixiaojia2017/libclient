#include "responsehdl.h"

ResponseHdl::ResponseHdl(QJsonObject* rsp):rsp(rsp){}

void ResponseHdl::deal(){
    if(rsp->take("result").toBool()){
        emit(onSuccess());
    }
    else{
        QString err=rsp->take("detail").toString();
        emit(onFailed(err));
    }
}

ResponseHdl::~ResponseHdl(){
    delete rsp;
}
