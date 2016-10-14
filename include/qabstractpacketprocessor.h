#ifndef QABSTRACTPACKETPROCESSOR_H
#define QABSTRACTPACKETPROCESSOR_H

#include <QObject>
#include <QString>
#include <string>
#include "qudpserver.h"

class QAbstractPacketProcessor : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractPacketProcessor(QObject *parent = 0) : QObject{parent} {}
signals:

public slots:
    virtual void printPackets(QUdpServer *server) = 0;
    virtual void printPacket(const std::string &packet) = 0;
    virtual void printPacket(const QString &packet) = 0;
};

#endif // QABSTRACTPACKETPROCESSOR_H
