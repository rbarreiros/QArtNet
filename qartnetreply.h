#ifndef QARTNETREPLY_H
#define QARTNETREPLY_H

#include "common.h"

#include <stdint.h>
#include <QObject>
#include <QByteArray>

struct artnet_reply_s {
  uint8_t  id[8];
  uint16_t opCode;
  uint8_t  ip[4];
  uint16_t port;
  uint8_t  verH;
  uint8_t  ver;
  uint8_t  subH;
  uint8_t  sub;
  uint8_t  oemH;
  uint8_t  oem;
  uint8_t  ubea;
  uint8_t  status;
  uint16_t estaman;
  uint8_t  shortname[ARTNET_SHORTNAME_LENGTH];
  uint8_t  longname[ARTNET_LONGNAME_LENGTH];
  uint8_t  nodereport[ARTNET_REPORT_LENGTH];
  uint8_t  numbportsH;
  uint8_t  numbports;
  uint8_t  porttypes[ARTNET_MAX_PORTS];
  uint8_t  goodinput[ARTNET_MAX_PORTS];
  uint8_t  goodoutput[ARTNET_MAX_PORTS];
  uint8_t  swin[ARTNET_MAX_PORTS];
  uint8_t  swout[ARTNET_MAX_PORTS];
  uint8_t  swvideo;
  uint8_t  swmacro;
  uint8_t  swremote;
  uint8_t  sp1;
  uint8_t  sp2;
  uint8_t  sp3;
  uint8_t  style;
  uint8_t  mac[ARTNET_MAC_SIZE];
  uint8_t  bindIp[4];
  uint8_t  bindIndex;
  uint8_t  status2;
  uint8_t  filler[26];
} PACKED;

typedef struct artnet_reply_s artnet_reply_t;

class QArtNetReply : public QObject
{
    Q_OBJECT
public:

    enum Style
    {
        NODE   = 0, // A DMX to/from Art-Net device
        CONTROLLER, // A lighting console
        MEDIA,      // A Media server
        ROUTE,      // A network routing device
        BACKUP,     // A backup device
        CONFIG,     // Configuration or diagnostics tool
        VISUAL      // A visualizer
    };

    enum Status
    {
        STATUS_UBEA_OK          = 0x01, // UBEA ok or corrupt
        STATUS_RDM_CAPABLE      = 0x02, // RDM Capable or not
        STATUS_BOOT_ROM         = 0x04, // Boot from ROM or Firmware
        STATUS_PORTAUTH_PANEL   = 0x10, // Network cfg from panel only
        STATUS_PORTAUTH_NETWORK = 0x20, // Network cfg from network
        STATUS_PORTAUTH_NOTUSED = 0x30,
        STATUS_INDICATOR_LOCATE = 0x40,
        STATUS_INDICATOR_MUTE   = 0x80,
        STATUS_INDICATOR_NORMAL = 0xc0
    };

    enum Status2
    {
        STATUS2_BROWSER_OK   = 0x01, // Node has browser config or not
        STATUS2_DHCP         = 0x02, // Node IP manual or from dhcp
        STATUS2_DHCP_CAPABLE = 0x04, // Node supports DHCP
        STATUS2_15BIT_PORT   = 0x08  // Node subnet 8 bit or 15 bit
    };

    enum GoodInput
    {
        GI_ERRORS              = 0x04,
        GI_INPUT_DISABLED      = 0x08,
        GI_INCLUDE_DMX512_TEXT = 0x10,
        GI_INCLUDE_DMX512_SIP  = 0x20,
        GI_INCLUDE_DMX512_TEST = 0x40,
        GI_DATA_RECEIVED       = 0x80
    };

    enum GoodOutput
    {
        GO_MERGE_LTP           = 0x02,
        GO_DMXOUT_SHORTCUT     = 0x04,
        GO_DMX_MERGING         = 0x08,
        GO_INCLUDE_DMX512_TEXT = 0x10,
        GO_INCLUDE_DMX512_SIP  = 0x20,
        GO_INCLUDE_DMX512_TEST = 0x40,
        GO_DATA_TRANSMITTING   = 0x80
    };

    explicit QArtNetReply(QObject *parent = 0);
    explicit QArtNetReply(QObject *parent, QByteArray datagram);

    void setSubnet(uint16_t subnet);
    void setOEM(uint16_t oem);
    void setUbea(uint16_t ubea);
    void setStatus(uint8_t status);
    void setEstaman(uint16_t estaman);
    void setShortName(QString sname);
    void setLongName(QString lname);
    void setNodeReport(QString report);
    void setNumPorts(uint8_t ports);
    void setStatus2(uint8_t status);

    void setPortType(uint8_t port, uint8_t type);
    void setGoodInput(uint8_t port, uint8_t status);
    void setGoodOutput(uint8_t port, uint8_t status);
    void setSwin(uint8_t port, uint8_t sw);
    void setSwout(uint8_t port, uint8_t sw);

    QByteArray toDatagram();

private:
    artnet_reply_t m_reply;
};

#endif // QARTNETREPLY_H
