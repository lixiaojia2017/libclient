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
        SocketThread(QString ip,quint16 port,QJsonDocument *obj,QObject *parent = 0);
        ~SocketThread();
    protected:
        virtual void run();

    private:
        QString ip;
        quint16 port;
        QTcpSocket *tcpSocket;
        QJsonDocument *rqt;
        QVariantMap* result;
    signals:
        void connectFailed();
        void onSuccess(QVariantMap*);
        void badRespond();
};


#endif // SOCKETTHREAD_H
