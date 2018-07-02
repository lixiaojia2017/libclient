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
        enum mode
        {
            normal,up,down
        };
        SocketThread(QString ip,quint16 port,const QJsonObject &obj,QObject *parent = 0);
        ~SocketThread();
        virtual void run();
        QTcpSocket* getSocket();
    protected:


    private:
        mode currMode = normal;
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
        // toggle mode
        void changeToUp();
        void changeToDown();
};


#endif // SOCKETTHREAD_H
