#include "qartnetpoll.h"

#include <QDebug>

QArtNetPoll::QArtNetPoll(QObject *parent)
    : QObject(parent)
{
    memcpy(m_poll.id, ARTNET_STRING, ARTNET_STRING_SIZE);
    m_poll.opCode = ARTNET_POLL;
    m_poll.verH = (ARTNET_VERSION >> 8) & 0xff;
    m_poll.ver = ARTNET_VERSION & 0xff;
    m_poll.prio = 0;

    enableVlc(false);
    enableUnicast(false);
    setSendDiagnostics(true);
    setReplyAlways(true);
}

QArtNetPoll::QArtNetPoll(QObject *parent, QByteArray dgram)
    : QObject(parent)
{
    memcpy(m_poll.id,
           dgram.left(ARTNET_STRING_SIZE).toStdString().c_str(),
           ARTNET_STRING_SIZE);
    m_poll.opCode = dgram.mid(8, 2).toInt(0, 16);
    m_poll.verH = (dgram.mid(11, 2).toInt(0, 16) >> 8) & 0xff;
    m_poll.ver = (dgram.mid(11, 2).toInt(0, 16) & 0xff);
    m_poll.ttm = dgram.mid(13, 1).toInt(0, 16);
    m_poll.prio = dgram.mid(14, 1).toInt(0, 16);

    qDebug() << "Code " << m_poll.opCode;
}

void QArtNetPoll::enableVlc(bool vlc)
{
    if(vlc)
        m_poll.ttm &= ~DISABLE_VLC;
    else
        m_poll.ttm |= DISABLE_VLC;
}

void QArtNetPoll::enableUnicast(bool unicast)
{
    if(unicast)
        m_poll.ttm |= UNICAST;
    else
        m_poll.ttm &= ~UNICAST;
}

void QArtNetPoll::setSendDiagnostics(bool diag)
{
    if(diag)
        m_poll.ttm |= SEND_DIAG;
    else
        m_poll.ttm &= ~SEND_DIAG;
}

void QArtNetPoll::setReplyAlways(bool reply)
{
    if(reply)
        m_poll.ttm |= ALWAYS;
    else
        m_poll.ttm &= ~ALWAYS;
}

QByteArray QArtNetPoll::toDatagram()
{
    return QByteArray(reinterpret_cast<const char *>(&m_poll), sizeof(artnet_poll_t));
}
