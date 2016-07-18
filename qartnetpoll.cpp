#include "qartnetpoll.h"

QArtNetPoll::QArtNetPoll(QObject *parent, QByteArray dgram)
    : QObject(parent)
{
    m_id = dgram.left(8);
    m_opCode = dgram.mid(8, 2).toInt(0, 16);
    m_versinfo = dgram.mid(11, 2).toInt(0, 16);
    m_ttm = dgram.mid(13, 1).toInt(0, 16);
    m_prio = dgram.mid(14, 1).toInt(0, 16);
}
