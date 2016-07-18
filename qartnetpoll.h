#ifndef QARTNETPOLL_H
#define QARTNETPOLL_H

#include <QObject>

class QArtNetPoll : public QObject
{
    Q_OBJECT
public:
    explicit QArtNetPoll(QObject *parent = 0);

signals:

public slots:
};

#endif // QARTNETPOLL_H