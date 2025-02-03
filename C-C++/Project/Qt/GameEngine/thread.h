#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include "mainwindow.h"

class thread : public MainWindow
{
    Q_OBJECT
public:
    thread();

public slots:
    void checkCondition();
};

#endif // THREAD_H
