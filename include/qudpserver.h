#ifndef QUDPSERVER_H
#define QUDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <deque>
#include <queue>

class QUdpServer : public QObject
{
    Q_OBJECT

public:
    explicit QUdpServer(const QHostAddress &hostAddress, unsigned int portNumber);
    //QUdpServer(const QUdpServer &other);
    //QUdpServer(QUdpServer &&other);
    ~QUdpServer();

    void resetSocket(const QHostAddress &hostAddress, unsigned int portNumber);
    bool nextDatagramAvailable();
    std::string nextDatagram();
signals:
    void datagramAvailable(QUdpServer *me);

private:
    QUdpSocket *_udpSocket;
    unsigned int _portNumber;
    QHostAddress _hostAddress;
    std::queue<std::string> _storedDatagrams;

    void processDatagram(const QByteArray &datagram);
    void clearDatagrams();

private slots:
    void readPendingDatagrams();
};

#endif // QUDPSERVER_H
