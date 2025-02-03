#ifndef OCRTHREAD_H
#define OCRTHREAD_H

#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QDir>

class OCRThread : public QThread
{
    Q_OBJECT
public:
    explicit OCRThread(QObject *parent = nullptr);

public slots:
    void startOCR();

signals:
    void emitTranslateLabel(QString& text);

private:
    QProcess* process;
};

#endif // OCRTHREAD_H
