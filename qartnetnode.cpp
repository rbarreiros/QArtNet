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

QByteArray QArtNetNode::ipToByteArray(QHostAddress ip)
{
    QByteArray out;
    QStringList sip = ip.toString().split(":");
    for(int i = 0; i < sip.count(); i++)
    {
        out.append(sip.at(i));
    }

    return out;
}

QByteArray QArtNetNode::getReplyPacket()
{
    QByteArray packet("Art-Net");

    packet.append((char)0);
    packet.append((char)0);
    packet.append((char)33);


    packet.append(ipToByteArray(m_ip));

    packet.append(QByteArray::number(ARTNET_UDP_PORT));

    packet.append(m_versinfo);
    packet.append(m_subnet);
    packet.append(m_oem);
    packet.append(m_ubea);
    packet.append(m_status);
    packet.append(m_estaman);
    packet.append(m_shortname);
    packet.append(m_longname);
    packet.append(getNodeReportString());
    packet.append(m_numports);

    for(int i = 0; i < ARTNET_MAX_PORTS; i++)
    {
        packet.append(m_porttypes[i]);
        packet.append(m_goodinput[i]);
        packet.append(m_goodoutput[i]);
        packet.append(m_swin[i]);
        packet.append(m_swout[i]);
    }

    packet.append(m_swvideo);
    packet.append(m_swmacro);
    packet.append(m_swremote);
    packet.append(3, (char)0);
    packet.append(m_style);
    packet.append(m_mac); // no null !!!
    packet.append(4, (char)0); // bindip
    packet.append((char)0); // bindIndex
    packet.append(m_status2);
    packet.append(26, (char)0);

    return packet;
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

void QArtNetNode::setStatusIndicator(artnet_status_indicator_t indicator)
{
    m_status = (indicator << 7);
}

void QArtNetNode::setStatusPortAuth(artnet_status_progauth_t pa)
{
    m_status = (pa << 5);
}

void QArtNetNode::setStatusBoot(artnet_status_boot_t boot)
{
    m_status = (boot << 3);
}

void QArtNetNode::setStatusRdm(artnet_status_rdm_t rdm)
{
    m_status = (rdm << 2);
}

void QArtNetNode::setStatusUbea(artnet_status_ubea_t ubea)
{
    m_status = (ubea << 1);
}

artnet_status_indicator_t QArtNetNode::getStatusIndicator()
{
    return (artnet_status_indicator_t)(m_status & (0x2 << 7));
}

artnet_status_progauth_t QArtNetNode::getStatusPortAuth()
{
    return (artnet_status_progauth_t)(m_status & (0x2 << 5));
}

artnet_status_boot_t QArtNetNode::getStatusBoot()
{
    return (artnet_status_boot_t)(m_status & (1 << 3));
}

artnet_status_rdm_t QArtNetNode::getStatusRdm()
{
    return (artnet_status_rdm_t)(m_status & (1 << 2));
}

artnet_status_ubea_t QArtNetNode::getStatusUbea()
{
    return (artnet_status_ubea_t)(m_status & (1 << 1));
}
