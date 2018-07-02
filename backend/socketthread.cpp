#include "socketthread.h"



SocketThread::SocketThread(QString ip,quint16 port,const QJsonObject &obj,QObject *parent):ip(ip),port(port),QThread(parent),rqt(QJsonDocument(obj))
{
    connect(this,&SocketThread::finished,this,&QThread::quit);
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
        QByteArray rqtData=rqt.toBinaryData();
        // detect whether it is a file protocol
        auto &&jsonObj = rqt.object();
        if(jsonObj.value("type").toString()=="LOAD")
        {
            transfer = new tcpFileTransfer(tcpSocket);
            connect(transfer,&tcpFileTransfer::onFail,this,[&]()
            {

            });
            connect(transfer,&tcpFileTransfer::onFinish,this,[&]()
            {

            });
            if(jsonObj.value("command").toString()=="up")
            {
                currMode = up;
            }
            else if(jsonObj.value("command").toString()=="down")
            {
                currMode = down;
            }
        }
        QByteArray sendData;
        QDataStream out(&sendData,QIODevice::WriteOnly);
        out << (qint8)'Q';
        out << (qint32)rqtData.size();
        out << rqtData;
        tcpSocket->write(sendData);
        tcpSocket->flush();
        tcpSocket->waitForBytesWritten(3000);
    }
    else{
        emit(connectFailed());
        tcpSocket->close();
        tcpSocket->deleteLater();
        this->quit();
        return;
    }
    tcpSocket->setReadBufferSize(4096);
    qint32 leftSize;
    if(tcpSocket->waitForReadyRead(10000)){
        QByteArray ReadData =tcpSocket->readAll();
        QDataStream in(&ReadData,QIODevice::ReadOnly);
        qint8 sign;
        in >> sign;
        if(sign=='A'){
            qint32 bytes;
            QByteArray rspData;
            in >> bytes;
            leftSize = bytes-ReadData.size();
            // to maintain the integrity and completeness of data
            // Note that ReadAll() does not actually read all, but a random size around 2000-4000 bytes
            while(leftSize>0)
            {
                tcpSocket->waitForReadyRead(3000);
                QByteArray &&add = tcpSocket->readAll();
                ReadData.append(add);
                leftSize -= add.size();
            }
            in >> rspData;
            if(rspData.size() != bytes){
                emit(badResponse());
            }
            else{
            QJsonDocument &&json=QJsonDocument::fromBinaryData(rspData);
            result=new QJsonObject;
            *result=json.object();
            // toggle mode ?
            if(currMode!=normal)
            {
                // if true, the file exists, and we can be ready to receive file
                if(result->value("result").toBool())
                {
                    if(currMode==up)
                    {
                        //transfer->sendHead();
                        transfer->sendData();
                    }
                    else  // download
                    {
                        transfer->receiveFile("./cache");
                        emit downloadComplete(transfer->fileName);
                        return;
                    }
                }
                else emit badResponse();
            }
            emit(onSuccess(result));
            }
        }
        else{
            emit(badResponse());
        }
    }
    else{
        emit(connectFailed());
    }
    if(currMode==normal)
    {
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        tcpSocket->deleteLater();
        emit(finished());
        this->quit();
    }
}

QTcpSocket* SocketThread::getSocket()
{
    return tcpSocket;
}
