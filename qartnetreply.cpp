#include "qartnetreply.h"

QArtNetReply::QArtNetReply(QObject *parent)
    : QObject(parent)
{
    // Fill with defaults
    memset(&m_reply, 0, sizeof(artnet_reply_t));

    memcpy(m_reply.id, ARTNET_STRING, ARTNET_STRING_SIZE);
    m_reply.opCode = htols(ARTNET_REPLY);
    m_reply.port = htols(ARTNET_UDP_PORT);
    m_reply.verH = (ARTNET_VERSION >> 8) & 0xff;
    m_reply.ver = (ARTNET_VERSION & 0xff);

    setSubnet(0); // todo
    setOEM(OEM);
    setUbea(0);
    setStatus(STATUS_INDICATOR_NORMAL | STATUS_PORTAUTH_NETWORK);
    setEstaman(ESTAMAN);

    setShortName("QArtnet Node");
    setLongName("QT QArtNetNode C++ Library");
    setNodeReport("OK");
    setNumPorts(0);

    setStatus2(STATUS2_BROWSER_OK | STATUS2_DHCP | STATUS2_DHCP_CAPABLE | STATUS2_15BIT_PORT);
}

QArtNetReply::QArtNetReply(QObject *parent, QByteArray datagram)
    : QObject(parent)
{
    memset(&m_reply, 0, sizeof(artnet_reply_t));

    memcpy(m_reply.id,
           datagram.left(ARTNET_STRING_SIZE).toStdString().c_str(),
           ARTNET_STRING_SIZE);

}

void QArtNetReply::setSubnet(uint16_t subnet)
{

}

void QArtNetReply::setOEM(uint16_t oem)
{

}

void QArtNetReply::setUbea(uint16_t ubea)
{

}

void QArtNetReply::setStatus(uint8_t status)
{

}

void QArtNetReply::setEstaman(uint16_t estaman)
{

}

void QArtNetReply::setShortName(QString sname)
{

}

void QArtNetReply::setLongName(QString lname)
{

}

void QArtNetReply::setNodeReport(QString report)
{

}

void QArtNetReply::setNumPorts(uint8_t ports)
{

}

void QArtNetReply::setStatus2(uint8_t status)
{

}

void QArtNetReply::setPortType(uint8_t port, uint8_t type)
{

}

void QArtNetReply::setGoodInput(uint8_t port, uint8_t status)
{

}

void QArtNetReply::setGoodOutput(uint8_t port, uint8_t status)
{

}

void QArtNetReply::setSwin(uint8_t port, uint8_t sw)
{

}

void QArtNetReply::setSwout(uint8_t port, uint8_t sw)
{

}
