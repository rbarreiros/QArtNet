#ifndef QARTNETPOLL_H
#define QARTNETPOLL_H

#include "common.h"

#include <stdint.h>
#include <QObject>
#include <QByteArray>

struct	artnet_poll_s {
  uint8_t  id[8];
  uint16_t opCode;
  uint8_t  verH;
  uint8_t  ver;
  uint8_t  ttm;
  uint8_t  prio;
} PACKED;

typedef struct artnet_poll_s artnet_poll_t;

class QArtNetPoll : public QObject
{
    Q_OBJECT
public:

    enum TTM
    {
        ALWAYS      = 0x02,
        SEND_DIAG   = 0x04,
        UNICAST     = 0x08,
        DISABLE_VLC = 0x10
    };

    explicit QArtNetPoll(QObject *parent = 0);
    explicit QArtNetPoll(QObject *parent, QByteArray dgram);

    QString getId() { return QString().fromLocal8Bit((char *)m_poll.id); }
    u_int16_t getOpcode() { return m_poll.opCode; }
    u_int16_t getVersion() { return ((m_poll.verH << 8) | m_poll.ver); }

    u_int8_t getPriority() { return m_poll.prio; }
    void setPriority(u_int8_t prio) { m_poll.prio = prio; }

    // VLC Enabled or not
    bool isVlcEnabled() { return !(m_poll.ttm & DISABLE_VLC); }
    void enableVlc(bool vlc);

    // Unicast or Broadcast messages
    bool isUnicast() { return (m_poll.ttm & UNICAST); }
    void enableUnicast(bool unicast);

    // Send poll replies or not
    bool sendDiagnostics() { return (m_poll.ttm & SEND_DIAG); }
    void setSendDiagnostics(bool diag);

    // Only send replies when an poll or address is received
    // or send whenever a change has been made
    bool replyAlways() { return (m_poll.ttm & ALWAYS); }
    void setReplyAlways(bool reply);

    QByteArray toDatagram();

private:
    artnet_poll_t m_poll;
};


#endif // QARTNETPOLL_H
