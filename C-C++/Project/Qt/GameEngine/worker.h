#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class worker : public QObject
{
    Q_OBJECT
public:
    worker();
    ~worker();

public slots:
    void checkCondition();
    void setstop();

private:

    bool stop = false;

signals:
    void deplacement();
    void check();
};

#endif // WORKER_H
