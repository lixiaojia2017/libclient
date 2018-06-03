#include "socketthread.h"



SocketThread::SocketThread(QString ip,quint16 port,QJsonDocument *obj,QObject *parent):ip(ip),port(port),QThread(parent),rqt(obj)
{
}
SocketThread::~SocketThread()
{
    tcpSocket->deleteLater();
}
void SocketThread::run()
{
    tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost(ip,port);
    if(tcpSocket->waitForConnected(10000)){
        QByteArray rqtData=rqt->toBinaryData();
        QByteArray sendData;
        QDataStream out(&sendData,QIODevice::WriteOnly);
        out << (qint8)'Q';
        out << (qint32)rqtData.size();
        out << rqtData;
        tcpSocket->write(sendData);
        tcpSocket->flush();
        delete rqt;
    }
    else{
        emit(connectFailed());
    }

    if(tcpSocket->waitForReadyRead(10000)){
        QByteArray &&ReadData =tcpSocket->readAll();
        QDataStream in(&ReadData,QIODevice::ReadOnly);
        qint8 sign;
        in >> sign;
        if(sign=='A'){
            qint32 bytes;
            QByteArray rspData;
            in >> bytes;
            in >> rspData;
            if(rspData.size() != bytes){
                emit(badResponse());
            }
            QJsonDocument &&json=QJsonDocument::fromBinaryData(rspData);
            result=new QJsonObject;
            *result=json.object();
            emit(onSuccess(result));
        }
        else{
            emit(badResponse());
        }
    }
    else{
        emit(connectFailed());
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket->deleteLater();
    this->quit();
}
