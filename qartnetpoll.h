#ifndef QARTNETPOLL_H
#define QARTNETPOLL_H

#include <QObject>

class QArtNetPoll : public QObject
{
    Q_OBJECT
public:
    explicit QArtNetPoll(QObject *parent = 0, QByteArray dgram = 0);

    QString getId() { return m_id; }
    u_int16_t getOpcode() { return m_opCode; }
    u_int16_t getVersion() { return m_versinfo; }
    u_int8_t getPriority() { return m_prio; }

    // VLC Enabled or not
    bool isVlcEnabled() { return !(m_ttm & (1 << 5)); }
    // Unicast or Broadcast messages
    bool isUnicast() { return (m_ttm & (1 << 4)); }
    // Send poll replies or not
    bool sendDiagnostics() { return (m_ttm & (1 << 3)); }
    // Only send replies when an poll or address is received
    // or send whenever a change has been made
    bool replyAlways() { return (m_ttm & (1 << 2)); }

private:
    QString m_id;
    u_int16_t m_opCode;
    u_int16_t m_versinfo;
    u_int8_t m_ttm;
    u_int8_t m_prio;
};


#endif // QARTNETPOLL_H
