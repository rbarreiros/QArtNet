#ifndef QARTNETNODE_H
#define QARTNETNODE_H

#include "qartnet_global.h"
#include "common.h"

#include <QObject>
#include <QHostAddress>

class QARTNETSHARED_EXPORT QArtNetNode : public QObject
{
    Q_OBJECT

public:
    explicit QArtNetNode(QObject *parent = 0);

    void parsePacket(QByteArray packet);
    QByteArray getReplyPacket();

    void setIp(QHostAddress ip) { m_ip = ip; }
    QHostAddress getIp() { return m_ip; }
    void setVersionInfo(u_int16_t vi) { m_versinfo = vi; }
    u_int16_t getVersionInfo() { return m_versinfo; }
    void setSubnet(u_int16_t subnet) { m_subnet = subnet; }
    u_int16_t getSubnet() { return m_subnet; }
    void setOem(u_int16_t oem) { m_oem = oem; }
    u_int16_t getOem() { return m_oem; }
    void setUbea(u_int8_t ubea) { m_ubea = ubea; }
    u_int8_t getUbea() { return m_ubea; }
    void setStatus(u_int8_t status) { m_status = status; }
    u_int8_t getStatus() { return m_status; }
    void setEstaman(u_int16_t esta) { m_estaman = esta; }
    u_int16_t getEstaman() { return m_estaman; }
    void setShortName(QString shortname) { m_shortname = shortname; }
    QString getShortName() { return m_shortname; }
    void setLongName(QString longname) { m_longname = longname; }
    QString getLongName() { return m_longname; }
    void setNodeReport(QString report) { m_nodereport = report; }
    QString getNodeReport() { return m_nodereport; }
    void setNumPorts(u_int16_t ports) { m_numports = ports; }
    u_int16_t getNumPorts() { return m_numports; }

    void setPortType(u_int8_t port, u_int8_t type);
    u_int8_t getPortType(u_int8_t port);
    void setGoodInput(u_int8_t port, u_int8_t input);
    u_int8_t getGoodInput(u_int8_t port);
    void setGoodOutput(u_int8_t port, u_int8_t output);
    u_int8_t getGoodOutput(u_int8_t port);
    void setSwin(u_int8_t port, u_int8_t swin);
    u_int8_t getSwin(u_int8_t port);
    void setSwout(u_int8_t port, u_int8_t swout);
    u_int8_t getSwout(u_int8_t port);

    void setSwVideo(u_int8_t video) { m_swvideo = video; }
    u_int8_t getSwVideo() { return m_swvideo; }
    void setSwMacro(u_int8_t macro) { m_swmacro = macro; }
    u_int8_t getSwMacro() { return m_swmacro; }
    void setSwRemote(u_int8_t remote) { m_swremote = remote; }
    u_int8_t getSwRemote() { return m_swremote; }
    void setStyle(u_int8_t style) { m_style = style; }
    u_int8_t getStyle() { return m_style; }

    void setMac(QString mac) { m_mac = mac; }
    QString getMac() { return m_mac; }

    void setStatus2(u_int8_t status) { m_status2 = status; }
    u_int8_t getStatus2() { return m_status2; }

    void setStatusIndicator(artnet_status_indicator_t indicator);
    void setStatusPortAuth(artnet_status_progauth_t pa);
    void setStatusBoot(artnet_status_boot_t boot);
    void setStatusRdm(artnet_status_rdm_t rdm);
    void setStatusUbea(artnet_status_ubea_t ubea);

    artnet_status_indicator_t getStatusIndicator();
    artnet_status_progauth_t getStatusPortAuth();
    artnet_status_boot_t getStatusBoot();
    artnet_status_rdm_t getStatusRdm();
    artnet_status_ubea_t getStatusUbea();

private:
    QHostAddress m_ip;                      // Node IP Address
    u_int16_t m_versinfo;                   // Firmware Version
    u_int16_t m_subnet;                     // Net switch + Subnet Switch
    u_int16_t m_oem;                        // OEM
    u_int8_t  m_ubea;                       // UBEA
    u_int8_t  m_status;
    u_int16_t m_estaman;                    // ESTA Manufacturer code
    QString   m_shortname;
    QString   m_longname;
    QString   m_nodereport;
    int16_t   m_numports;
    u_int8_t  m_porttypes[ARTNET_MAX_PORTS]; // Type of ports
    u_int8_t  m_goodinput[ARTNET_MAX_PORTS];
    u_int8_t  m_goodoutput[ARTNET_MAX_PORTS];
    u_int8_t  m_swin[ARTNET_MAX_PORTS];
    u_int8_t  m_swout[ARTNET_MAX_PORTS];
    u_int8_t  m_swvideo;
    u_int8_t  m_swmacro;
    u_int8_t  m_swremote;
    u_int8_t  m_style;
    QString   m_mac;
    u_int8_t  m_status2;

    QList<QHostAddress> m_serversIp;
};

#endif // QARTNETNODE_H
