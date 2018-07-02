#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
class SocketThread : public QThread
{
    Q_OBJECT
    public:
        SocketThread(QString ip,quint16 port,const QJsonObject &obj,QObject *parent = 0);
        ~SocketThread();
        virtual void run();
    protected:


    private:
        QString ip;
        quint16 port;
        QTcpSocket *tcpSocket;
        QJsonDocument rqt;
        QJsonObject* result;
    signals:
        void connectFailed();
        void onSuccess(QJsonObject*);
        void badResponse();
        void finished();
};


#endif // SOCKETTHREAD_H
