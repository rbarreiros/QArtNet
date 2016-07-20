#include "qartnet.h"

#include <QUdpSocket>
#include <QDebug>

QArtNet::QArtNet(QObject *parent)
    : QObject(parent)
{
    m_socket = new QUdpSocket(this);
    m_self = new QArtNetNode(this);

    m_nodeList.clear();
}

QArtNet::~QArtNet()
{
    if(m_socket->isOpen())
        m_socket->close();
    delete m_socket;
    delete m_self;
}

bool QArtNet::start(QNetworkInterface iface)
{
    m_iface = iface;

    if(iface.addressEntries().count() == 0)
        return false;

    for(int i = 0; i < iface.addressEntries().count(); i++)
    {
        // Ignore IPv6
        if(!iface.addressEntries().at(i).ip().toIPv4Address())
            continue;

        m_selfIp = iface.addressEntries().at(i).ip();
        m_broadcast = iface.addressEntries().at(i).broadcast();
        break;
    }

    /*
    if(!m_socket->bind(m_selfIp, ARTNET_UDP_PORT, QAbstractSocket::ReuseAddressHint))
        return false;
        */
    qDebug() << "Bound to Interface " << iface.humanReadableName() << " with IP " << m_selfIp.toString();

    if(!m_socket->bind(QHostAddress::Any, ARTNET_UDP_PORT, QAbstractSocket::ReuseAddressHint))
        return false;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

    createLocalNode();

    // Send a poll request to see who's around
    sendPoll();

    return true;
}

void QArtNet::stop()
{
    disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
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

void QArtNet::processPacket(QHostAddress sender, u_int16_t port, QByteArray datagram)
{
    // Is this a valid ArtNet packet ?
    QString id(datagram.left(8));
    if(id != QString("Art-Net"))
        return;

    qDebug() << "Got ArtNet Packet";

    u_int16_t opCode = datagram.at(8) + (datagram.at(9) << 8);

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
    m_self->setIp(m_selfIp);

    m_self->setVersionInfo(14);
    m_self->setSubnet(0); // todo

    m_self->setOem(OEM);

    m_self->setUbea(0);

    m_self->setStatus(STATUS_INDICATOR_NORMAL | STATUS_PORTAUTH_NETWORK);
    m_self->setEstaman(ESTAMAN);

    m_self->setShortName("QArtnet Node");
    m_self->setLongName("QT QArtNetNode C++ Library");
    m_self->setNodeReport("OK");
    m_self->setNumPorts(0);

    m_self->setController(true);
    m_self->setAlwaysReply(true);
    m_self->setSendDiagnostics(true);
    m_self->setUnicast(true);

    m_self->setMac(m_iface.hardwareAddress());
    m_self->setStatus2(STATUS2_BROWSER_OK | STATUS2_DHCP | STATUS2_DHCP_CAPABLE | STATUS2_15BIT_PORT);
}

void QArtNet::sendPoll()
{
    artnet_poll_t poll;

    memcpy(poll.id, ARTNET_STRING, ARTNET_STRING_SIZE);
    poll.opCode = htols(ARTNET_POLL);
    poll.verH = 0;
    poll.ver = ARTNET_VERSION;
    poll.ttm = (ARTNET_TTM_ALWAYS | ARTNET_TTM_SEND_DIAG);
    poll.prio = 0;

    m_socket->writeDatagram(QByteArray(reinterpret_cast<const char *>(&poll),
                                       sizeof(artnet_poll_t)), m_broadcast, ARTNET_UDP_PORT);
    qDebug() << "Sent Poll";
}

void QArtNet::processPoll(QHostAddress sender, u_int16_t port, QArtNetPoll *poll)
{
    (void)sender;
    (void)port;
    // Poll replies are always directed broadcast (for example 10.255.255.255, 192.168.1.255)
    m_self->setAlwaysReply(poll->replyAlways());
    m_self->setSendDiagnostics(poll->sendDiagnostics());
    m_self->setUnicast(poll->isUnicast());

    QByteArray reply = m_self->getReplyPacket();
    m_socket->writeDatagram(reply.data(), reply.size(), m_broadcast, ARTNET_UDP_PORT);
}
