#include "worker.h"
#include "qdebug.h"
#include "qthread.h"
#include <QMessageBox>

worker::worker() {
    qDebug() << "Worker created.";
}

worker::~worker()
{}

void worker::checkCondition()
{
    stop = false;
    while(1)
    {
        QThread::sleep(1);
        emit check();
        emit deplacement();
    }
}

void worker::setstop()
{
    stop = true;
    qDebug() << stop;
}
