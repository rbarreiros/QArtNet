#ifndef QARTNETNODE_H
#define QARTNETNODE_H

#include <QObject>

class QArtNetNode : public QObject
{
    Q_OBJECT
public:
    explicit QArtNetNode(QObject *parent = 0);

signals:

public slots:
};

#endif // QARTNETNODE_H