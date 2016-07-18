#include "qartnetnode.h"

QArtNetNode::QArtNetNode(QObject *parent)
    : QObject(parent)
{
    m_serversIp.clear();
}

void QArtNetNode::parsePacket(QByteArray packet)
{

}

QByteArray QArtNetNode::getReplyPacket()
{

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
