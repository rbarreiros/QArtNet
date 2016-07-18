#include "qartnet.h"

#include <QUdpSocket>

QArtNet::QArtNet(QObject *parent)
    : QObject(parent)
{
    m_socket = new QUdpSocket(this);

    m_nodeList.clear();
    createLocalNode();
}

QArtNet::~QArtNet()
{

}

bool QArtNet::start(QHostAddress ifaceIp)
{
    if(!m_socket->bind(ifaceIp, ARTNET_UDP_PORT, QAbstractSocket::ReuseAddressHint))
        return false;

    m_selfIp = ifaceIp;
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void QArtNet::processPacket(QHostAddress sender, u_int16_t port, QByteArray datagram)
{
    // Is this a valid ArtNet packet ?
    QString id(datagram.left(8));
    if(id != QString("Art-Net"))
        return;

    u_int16_t opCode = datagram.mid(8, 2).toInt(0, 16);
    switch(opCode)
    {
    case ARTNET_POLL:
        processPoll(sender, port, new QArtNetPoll(this, datagram));
        break;
    case ARTNET_REPLY:
        break;
    case ARTNET_DMX:
        break;
    case ARTNET_ADDRESS:
    case ARTNET_INPUT:
    case ARTNET_TODREQUEST:
    case ARTNET_TODDATA:
    case ARTNET_TODCONTROL:
    case ARTNET_RDM:
    case ARTNET_VIDEOSETUP:
    case ARTNET_VIDEOPALETTE:
    case ARTNET_VIDEODATA:
    case ARTNET_MACMASTER:
    case ARTNET_MACSLAVE:
    case ARTNET_FIRMWAREMASTER:
    case ARTNET_FIRMWAREREPLY:
    case ARTNET_IPPROG:
    case ARTNET_IPREPLY:
    case ARTNET_MEDIA:
    case ARTNET_MEDIAPATCH:
    case ARTNET_MEDIACONTROLREPLY:
    default:
        // Not implemented
        break;
    };
}

void QArtNet::createLocalNode()
{
    /*
    if(m_selfIp == QHostAddress::Any)
        m_self->setIp(getFirstLocalIp());
    */

    m_self->setVersionInfo(14);
    m_self->setSubnet(0); // todo

    u_int16_t oem = (0x04 << 8) & 0x31;
    m_self->setOem(oem);

    m_self->setUbea(0);

    m_self->setStatusIndicator(STATUS_INDICATOR_NORMAL);
    m_self->setStatusPortAuth(STATUS_PORTAUTH_NETWORK);
    m_self->setEstaman(0x5944);

    m_self->setShortName("QArtnet Node");
    m_self->setLongName("QT QArtNetNode C++ Library");
    m_self->setNodeReport("Node OK");

}

void QArtNet::readPendingDatagrams()
{
    while(m_socket->hasPendingDatagrams())
    {
        QByteArray dgram;
        dgram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        u_int16_t port;

        m_socket->readDatagram(dgram.data(), dgram.size(), &sender, &port);
        processPacket(sender, port, dgram);
    }
}

void QArtNet::processPoll(QHostAddress sender, u_int16_t port, QArtNetPoll *poll)
{

}
