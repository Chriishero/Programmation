#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class Worker : public QThread
{
public:
    explicit Worker(QObject *parent = nullptr);
};

#endif // WORKER_H
