#ifndef QUDPPACKETPROCESSOR_H
#define QUDPPACKETPROCESSOR_H

#include <QObject>
#include <iostream>
#include "qudpserver.h"
#include "qabstractpacketprocessor.h"

class QUdpPacketProcessor : public QAbstractPacketProcessor
{
    Q_OBJECT

public:
    explicit QUdpPacketProcessor(QObject *parent = 0) : QAbstractPacketProcessor{parent} {}

signals:

public slots:
    void printPackets(QUdpServer *server)
    {
        while (server->nextDatagramAvailable()) {
            std::cout << server->nextDatagram() << std::endl;
        }
    }

    void printPacket(const std::string &packet) { std::cout << packet << std::endl; }
    void printPacket(const QString &packet) { std::cout << packet.toStdString() << std::endl; }
};

#endif // QUDPPACKETPROCESSOR_H
