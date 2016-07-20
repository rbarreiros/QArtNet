#ifndef QARTNET_H
#define QARTNET_H

#include "qartnet_global.h"
#include "common.h"
#include "qartnetnode.h"
#include "qartnetpoll.h"

#include <QObject>
#include <QHostAddress>
#include <QNetworkInterface>

class QUdpSocket;

class QARTNETSHARED_EXPORT QArtNet : public QObject
{
    Q_OBJECT

public:
    QArtNet(QObject *parent);
    virtual ~QArtNet();

    bool start(QNetworkInterface iface);
    void stop();

    void sendPoll();
    void sendPollReply();
    void sendDmx();
    void sendRawDmx();
    void sendAddress();
    void sendInput();
    void sendFirmware();
    void sendFirmwareReply();
    void sendTodRequest();
    void sendTodControl();
    void sendRdm();
    void sendRdmDevice();

    void addRdmDevice();
    void removeRdmDevice();

signals:
    void artnetPacketReceived();
    void artnetPacketSent();
    void artnetPollReceived();
    void artnetReplyReceived();
    void artnetDmxReceived();
    void artnetAddressReceived();
    void artnetInputReceived();
    void artnetTodRequestReceived();
    void artnetTodDataReceived();
    void artnetTodControlReceived();
    void artnetRdmReceived();
    void artnetIpProgReceived();
    void artnetFirmwareReceived();
    void artnetFirmwareReplyReceived();

private slots:
    void readPendingDatagrams();

private:
    void processPoll(QHostAddress sender, u_int16_t port, QArtNetPoll *poll);

    void processPacket(QHostAddress sender, u_int16_t port, QByteArray datagram);
    void createLocalNode();

    QUdpSocket *m_socket;
    QArtNetNode *m_self; // Local node
    QList<QArtNetNode> m_nodeList;
    QHostAddress m_selfIp;
    QHostAddress m_broadcast;
    QNetworkInterface m_iface;
};

#endif // QARTNET_H
