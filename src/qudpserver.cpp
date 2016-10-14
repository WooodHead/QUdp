#include "qudpserver.h"

/*Begin constructors*/
QUdpServer::QUdpServer(const QHostAddress &hostAddress, unsigned int portNumber) :
    _udpSocket{ new QUdpSocket{this} },
    _portNumber{portNumber},
    _hostAddress{hostAddress},
    _storedDatagrams{ std::queue<std::string>{} }
{
    this->_udpSocket->bind(this->_hostAddress, this->_portNumber);
    connect(this->_udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

/* TODO: Figure out the below
QUdpServer::QUdpServer(const QUdpServer &other) :
    QObject{other.parent},
    _udpSocket( new QUdpSocket( *(other._udpSocket), other.parent())),
    _portNumber{other._portNumber},
    _hostAddress{other._hostAddress},
    _storedDatagrams{ other._storedDatagrams }
{

}

QUdpServer::QUdpServer(QUdpServer &&other) :
    _udpSocket{ std::move(other._udpSocket) },
    _portNumber{ std::move(other._portNumber) },
    _hostAddress{ std::move(other._hostAddress) },
    _storedDatagrams{ std::move(other._storedDatagrams) }
{

}
*/
/*End constructors*/

/*Begin public members*/
void QUdpServer::resetSocket(const QHostAddress &hostAddress, unsigned int portNumber)
{
    this->_hostAddress = hostAddress;
    this->_portNumber = portNumber;
    this->clearDatagrams();
    this->_udpSocket->bind(this->_hostAddress, this->_portNumber);
}

bool QUdpServer::nextDatagramAvailable()
{
    return !(this->_storedDatagrams.empty());
}

std::string QUdpServer::nextDatagram()
{
    std::string returnString{this->_storedDatagrams.front()};
    this->_storedDatagrams.pop();
    return returnString;
}
/*End public members*/

/*Begin private members*/
void QUdpServer::processDatagram(const QByteArray &datagram)
{
    this->_storedDatagrams.push(datagram.toStdString());
}

void QUdpServer::clearDatagrams()
{
    while (!(this->_storedDatagrams.empty())) {
        this->_storedDatagrams.pop();
    }
}

/*End private members*/

/*Begin private slots*/
void QUdpServer::readPendingDatagrams()
{
    while (this->_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(this->_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        this->_udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);\
        processDatagram(datagram);
    }
    emit(datagramAvailable(this));
}
/*End private slots*/

QUdpServer::~QUdpServer()
{
    delete this->_udpSocket;
}

