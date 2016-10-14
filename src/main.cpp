#include <QCoreApplication>
#include "qudpserver.h"
#include "qudppacketprocessor.h"

int main(int argc, char *argv[])
{
    QCoreApplication qApplication(argc, argv);
    QUdpServer *hostServer = new QUdpServer(QHostAddress::LocalHost, 8888);
    QUdpPacketProcessor *packetPrinter = new QUdpPacketProcessor();
    QCoreApplication::connect(hostServer, SIGNAL(datagramAvailable(QUdpServer *)), packetPrinter, SLOT(printPackets(QUdpServer *)));
    return qApplication.exec();
}
