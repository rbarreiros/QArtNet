#include "qartnetnode.h"
#include "common.h"

#include <QDataStream>

QArtNetNode::QArtNetNode(QObject *parent)
    : QObject(parent),
      m_ip(QHostAddress::Any),
      m_versinfo(0),
      m_subnet(0),
      m_oem(0),
      m_ubea(0),
      m_status(0),
      m_estaman(0),
      m_shortname(""),
      m_longname(""),
      m_nodereport(""),
      m_numports(0),
      m_swvideo(0),
      m_swmacro(0),
      m_swremote(0),
      m_style(0),
      m_mac(""),
      m_status2(0),
      m_isController(false),
      m_sendDiagnostics(true),
      m_unicast(false),
      m_alwaysReply(true)
{
    for(int i = 0; i < ARTNET_MAX_PORTS; i++)
    {
        m_porttypes[i] = 0;
        m_goodinput[i] = 0;
        m_goodoutput[i] = 0;
        m_swin[i] = 0;
        m_swout[i] = 0;
    }
}

void QArtNetNode::parsePollReplyPacket(QByteArray packet)
{
    (void)packet;
}

void QArtNetNode::ipToArray(QHostAddress ip, unsigned char *dest)
{
    QStringList sip = ip.toString().split(".");
    for(int i = 0; i < sip.count(); i++)
    {
        dest[i] = sip.at(i).toInt();
    }
}

void QArtNetNode::macToArray(QString mac, unsigned char *dest)
{
    QStringList sm = mac.split(":");
    for(int i = 0; i < sm.count(); i++)
    {
        dest[i] = sm.at(i).toInt(0, 16);
    }
}

QByteArray QArtNetNode::getReplyPacket()
{
    artnet_reply_t reply;
    memset((char *)&reply, 0, sizeof(artnet_reply_t));

    memcpy(reply.id, ARTNET_STRING, ARTNET_STRING_SIZE);
    reply.opCode = htols(ARTNET_REPLY);

    qDebug() << m_ip.toString();
    ipToArray(m_ip, reply.ip);
    reply.port = htols(ARTNET_UDP_PORT);
    reply.verH = (m_versinfo >> 8) & 0xff;
    reply.ver = m_versinfo & 0xff;
    reply.subH = (m_subnet >> 8) & 0xff;
    reply.sub = m_subnet & 0xff;
    reply.oemH = (m_oem >> 8) & 0xff;
    reply.oem = m_oem & 0xff;
    reply.ubea = m_ubea;
    reply.status = m_status;
    reply.estaman[1] = (m_estaman >> 8) & 0xff;
    reply.estaman[0] = (m_estaman & 0xff);
    memcpy(reply.shortname, m_shortname.toStdString().c_str(), ARTNET_SHORTNAME_LENGTH);
    memcpy(reply.longname, m_longname.toStdString().c_str(), ARTNET_LONGNAME_LENGTH);
    memcpy(reply.nodereport, getNodeReportString().toStdString().c_str(), ARTNET_REPORT_LENGTH);
    reply.numbportsH = (m_numports >> 8) & 0xff;
    reply.numbports = (m_numports & 0xff);
    macToArray(m_mac, reply.mac);
    reply.status2 = m_status2;

    ipToArray(m_ip, reply.bindIp);
    reply.bindIndex = 0;

    for(int i = 0; i < ARTNET_MAX_PORTS; i++)
    {
        reply.porttypes[i] = m_porttypes[i];
        reply.goodinput[i] = m_goodinput[i];
        reply.goodoutput[i] = m_goodoutput[i];
        reply.swin[i] = m_swin[i];
        reply.swout[i] = m_swout[i];
    }

    reply.swvideo = m_swvideo;
    reply.swmacro = m_swmacro;
    reply.swremote = m_swremote;
    reply.style = m_style;


    return QByteArray(reinterpret_cast<const char *>(&reply),
                      sizeof(artnet_reply_t));
}

QString QArtNetNode::getNodeReportString()
{
    // TODO
    return QString("Node OK");
}

void QArtNetNode::setPortType(u_int8_t port, u_int8_t type)
{
    if(port > ARTNET_MAX_PORTS)
        return;
    m_porttypes[port] = type;
}

u_int8_t QArtNetNode::getPortType(u_int8_t port)
{
    if(port > ARTNET_MAX_PORTS)
        return 0;
    return m_porttypes[port];
}

void QArtNetNode::setGoodInput(u_int8_t port, u_int8_t input)
{
    if(port > ARTNET_MAX_PORTS)
        return;
    m_goodinput[port] = input;
}

u_int8_t QArtNetNode::getGoodInput(u_int8_t port)
{
    if(port > ARTNET_MAX_PORTS)
        return 0;
    return m_goodinput[port];
}

void QArtNetNode::setGoodOutput(u_int8_t port, u_int8_t output)
{
    if(port > ARTNET_MAX_PORTS)
        return;
    m_goodoutput[port] = output;
}

u_int8_t QArtNetNode::getGoodOutput(u_int8_t port)
{
    if(port > ARTNET_MAX_PORTS)
        return 0;
    return m_goodoutput[port];
}

void QArtNetNode::setSwin(u_int8_t port, u_int8_t swin)
{
    if(port > ARTNET_MAX_PORTS)
        return;
    m_swin[port] = swin;
}

u_int8_t QArtNetNode::getSwin(u_int8_t port)
{
    if(port > ARTNET_MAX_PORTS)
        return 0;
    return m_swin[port];
}

void QArtNetNode::setSwout(u_int8_t port, u_int8_t swout)
{
    if(port > ARTNET_MAX_PORTS)
        return;
    m_swout[port] = swout;
}

u_int8_t QArtNetNode::getSwout(u_int8_t port)
{
    if(port > ARTNET_MAX_PORTS)
        return 0;
    return m_swout[port];
}
