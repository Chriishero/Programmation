#include "ocrthread.h"

OCRThread::OCRThread(QObject *parent)
    : QThread{parent}
{}

void OCRThread::startOCR()
{
    QString pcUserName = QDir::home().dirName(); // récupère le nom d'utilisateur de la sessions Windows
    QString directoryPath = QString("C:/Users/%1/Pictures/Screenshots").arg(pcUserName);
    QDir directory(directoryPath);

    // Récupère le nom de tous les captures d'écran enregistré dans le dossier 'directory'
    QStringList screenshots = directory.entryList(QStringList() << "*.png" << "*.PNG" << "*.jpg" << "*.JPG", QDir::Files);
    QString penultimateScreenShot = screenshots.last();
    QString lastScreenShot = penultimateScreenShot;

    /*while(lastScreenShot == penultimateScreenShot)
    {
        QStringList screenshots = directory.entryList(QStringList() << "*.png" << "*.PNG" << "*.jpg" << "*.JPG", QDir::Files);
        QString lastScreenShot = screenshots.last();
        QTimer::singleShot(3000, [&lastScreenShot]() -> void{
            qDebug() << lastScreenShot;
        });

    }*/
    qDebug() << "dernière capture : " << lastScreenShot;

    process = new QProcess(this);

    QList<QString> argList;
    argList.push_back(directoryPath + QString("/%1").arg(lastScreenShot));
    argList.push_back("stdout");

    process->start("Tesseract-OCR/tesseract.exe", QStringList() << argList);

    connect(process, &QProcess::readyReadStandardOutput, [this]() {
        QByteArray output = process->readAllStandardOutput();
        QString ocrText = QString::fromLocal8Bit(output);
        qDebug() << "Output OCR :" << ocrText;
        emit emitTranslateLabel(ocrText);

    });
}
